#include "data_bundle_manager.h"
#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <cstring>
#include <cerrno>

// ESP-IDF Headers for SD Card and Logging
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "esp_log.h"
#include "esp_timer.h" // For getting time for unique filenames

static const char* TAG = "BundleMgr";

DataBundleManager::DataBundleManager() : isRecording(false) {}

DataBundleManager::~DataBundleManager() {
    // Optional: Unmount if object destroyed
    // esp_vfs_fat_sdmmc_unmount();
}

// ==========================================
// 1. HARDWARE INIT (ESP-IDF Native)
// ==========================================
bool DataBundleManager::initStorage() {
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    sdmmc_card_t *card;
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    
    // CrowPanel usually uses SDMMC Slot 1 (4-bit mode)
    // If your board uses SPI, we would swap this for 'sdspi_host_t'
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    slot_config.width = 1; // Try 1-bit mode first if 4-bit is unstable
    // slot_config.width = 4; // Use 4-bit for speed if pins allow

    esp_err_t ret = esp_vfs_fat_sdmmc_mount(MOUNT_POINT, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s).", esp_err_to_name(ret));
        }
        return false;
    }

    ESP_LOGI(TAG, "SD Card mounted at %s", MOUNT_POINT);
    
    // Create bundles directory
    struct stat st = {0};
    if (stat(MOUNT_POINT "/bundles", &st) == -1) {
        mkdir(MOUNT_POINT "/bundles", 0777);
    }

    loadManifest();
    return true;
}

StorageStatus DataBundleManager::getStorageStatus() {
    StorageStatus status = {0, 0, 0, false};
    
    struct statvfs vfs;
    
    // statvfs returns 0 on success
    if (statvfs(MOUNT_POINT, &vfs) == 0) {
        status.isDetected = true;
        
        // f_bsize = block size, f_blocks = total blocks, f_bfree = free blocks
        // We calculate in KB to avoid 32-bit integer overflow on bytes
        uint64_t blockSize = vfs.f_bsize;
        
        status.totalKBytes = (vfs.f_blocks * blockSize) / 1024;
        status.freeKBytes = (vfs.f_bfree * blockSize) / 1024;
        status.usedKBytes = status.totalKBytes - status.freeKBytes;
    } else {
        ESP_LOGW(TAG, "Failed to get storage stats. Card might be missing.");
    }
    
    return status;
}

// ==========================================
// 2. RECORDING LOGIC
// ==========================================

bool DataBundleManager::startRecording(const std::string& sensorName, const std::string& date) {
    if (isRecording) return false;

    currentSensorName = sensorName;
    currentStartDate = date;
    
    // Create a temp file path: /sdcard/bundles/temp_123456.csv
    int64_t timestamp = esp_timer_get_time();
    char buf[64];
    snprintf(buf, sizeof(buf), "%s/bundles/temp_%lld.csv", MOUNT_POINT, timestamp);
    tempFilePath = std::string(buf);

    FILE* f = fopen(tempFilePath.c_str(), "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open temp file for writing");
        return false;
    }

    // Write Header
    fprintf(f, "Time,Part,Value\n");
    fclose(f);

    isRecording = true;
    ESP_LOGI(TAG, "Recording started: %s", tempFilePath.c_str());
    return true;
}

bool DataBundleManager::logData(const std::string& time, const std::string& partName, const std::string& value) {
    if (!isRecording) return false;

    FILE* f = fopen(tempFilePath.c_str(), "a"); // 'a' for append
    if (f == NULL) return false;

    // CSV Format: Time,Part,Value
    fprintf(f, "%s,%s,%s\n", time.c_str(), partName.c_str(), value.c_str());
    fclose(f);
    
    return true;
}

void DataBundleManager::discardCurrentRecording() {
    if (!isRecording) return;

    // Delete the temporary file
    if (remove(tempFilePath.c_str()) != 0) {
        ESP_LOGE(TAG, "Failed to delete temp file");
    } else {
        ESP_LOGI(TAG, "Recording discarded");
    }

    isRecording = false;
    tempFilePath = "";
}

void DataBundleManager::stopAndSaveRecording() {
    if (!isRecording) return;

    // 1. Rename temp file to final file
    int64_t timestamp = esp_timer_get_time();
    char finalPathBuf[64];
    snprintf(finalPathBuf, sizeof(finalPathBuf), "%s/bundles/data_%lld.csv", MOUNT_POINT, timestamp);
    std::string finalPath(finalPathBuf);

    if (rename(tempFilePath.c_str(), finalPath.c_str()) != 0) {
        ESP_LOGE(TAG, "Rename failed");
        return;
    }

    // 2. Create Metadata
    BundleMetadata meta;
    meta.startDate = currentStartDate;
    meta.sensorName = currentSensorName;
    meta.filePath = finalPath;

    // 3. FIFO Logic: Ensure max 30
    if (bundles.size() >= MAX_TOTAL_BUNDLES) {
        // Remove the oldest (index 0)
        deleteBundle(0);
    }

    // 4. Add new to end
    bundles.push_back(meta);

    // 5. Persist
    saveManifest();

    isRecording = false;
    tempFilePath = "";
    ESP_LOGI(TAG, "Recording saved: %s", finalPath.c_str());
}

// ==========================================
// 3. MANAGEMENT LOGIC
// ==========================================

void DataBundleManager::deleteBundle(int index) {
    if (index < 0 || index >= (int)bundles.size()) return;

    // 1. Delete actual file
    const char* path = bundles[index].filePath.c_str();
    struct stat st;
    if (stat(path, &st) == 0) {
        remove(path);
    }

    // 2. Remove from vector
    bundles.erase(bundles.begin() + index);

    // 3. Update manifest
    saveManifest();
}

void DataBundleManager::deleteAllBundles() {
    for (const auto& b : bundles) {
        remove(b.filePath.c_str());
    }
    bundles.clear();
    saveManifest(); // will write an empty file
}

int DataBundleManager::getBundleCount() const {
    return (int)bundles.size();
}

std::vector<BundleMetadata> DataBundleManager::getBundlesForPage(int pageIndex) {
    std::vector<BundleMetadata> pageItems;
    int start = pageIndex * MAX_BUNDLES_PER_PAGE;

    if (start >= (int)bundles.size()) return pageItems;

    for (int i = 0; i < MAX_BUNDLES_PER_PAGE; ++i) {
        int idx = start + i;
        if (idx < (int)bundles.size()) {
            pageItems.push_back(bundles[idx]);
        } else {
            break;
        }
    }
    return pageItems;
}

std::vector<DataPoint> DataBundleManager::loadDataFromBundle(int index) {
    std::vector<DataPoint> data;
    if (index < 0 || index >= (int)bundles.size()) return data;

    FILE* f = fopen(bundles[index].filePath.c_str(), "r");
    if (f == NULL) return data;

    char line[128];
    // Skip header
    fgets(line, sizeof(line), f);

    while (fgets(line, sizeof(line), f)) {
        // Strip newline
        line[strcspn(line, "\r\n")] = 0;
        
        std::vector<std::string> parts = splitString(line, ',');
        if (parts.size() >= 3) {
            DataPoint dp;
            dp.time = parts[0];
            dp.partName = parts[1];
            dp.value = parts[2];
            data.push_back(dp);
        }
    }
    fclose(f);
    return data;
}

// ==========================================
// 4. PERSISTENCE HELPERS
// ==========================================

void DataBundleManager::saveManifest() {
    std::string manPath = std::string(MOUNT_POINT) + "/bundles/manifest.txt";
    FILE* f = fopen(manPath.c_str(), "w");
    if (f == NULL) return;

    // Format: Date|SensorName|FilePath
    for (const auto& b : bundles) {
        fprintf(f, "%s|%s|%s\n", b.startDate.c_str(), b.sensorName.c_str(), b.filePath.c_str());
    }
    fclose(f);
}

void DataBundleManager::loadManifest() {
    bundles.clear();
    std::string manPath = std::string(MOUNT_POINT) + "/bundles/manifest.txt";
    FILE* f = fopen(manPath.c_str(), "r");
    if (f == NULL) return;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = 0; // trim newline
        if (strlen(line) == 0) continue;

        std::vector<std::string> parts = splitString(line, '|');
        if (parts.size() == 3) {
            BundleMetadata meta;
            meta.startDate = parts[0];
            meta.sensorName = parts[1];
            meta.filePath = parts[2];
            bundles.push_back(meta);
        }
    }
    fclose(f);
    ESP_LOGI(TAG, "Loaded %d bundles", (int)bundles.size());
}

// Simple C++ split string helper without generic algorithms
std::vector<std::string> DataBundleManager::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start));
    return tokens;
}