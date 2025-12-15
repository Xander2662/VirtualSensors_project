#include "data_bundle_manager.hpp"

// We include these ONLY for the hardware init
// They are BUILT-IN to the ESP32 Board package (no download needed)
#include <SD.h>
#include <FS.h>

// Standard C Headers
#include <sys/stat.h>

// On Arduino ESP32, the SD card is mapped to "/sd" by default
#define MOUNT_POINT "/sd"

DataBundleManager::DataBundleManager() {
    isMounted = false;
    isRecording = false;
}

// ==========================================
// 1. HARDWARE INIT (The only "Arduino" part)
// ==========================================
bool DataBundleManager::initStorage() {
    if (isMounted) return true;

    // CrowPanel 7.0 Hardware Config:
    // Usually uses default VSPI pins.
    // If it fails, try SD.begin(10) or SD.begin(SD_CS_PIN)
    
    if (!SD.begin()) {
        return false;
    }

    // Now that SD.begin() worked, the file system is live.
    // We can switch to pure C++ now.
    isMounted = true;

    // Create bundles directory using standard C
    // Note: Arduino SD wrapper maps "/sd" as root, so we just ask for "/bundles"
    if (!SD.exists("/bundles")) {
        SD.mkdir("/bundles");
    }

    loadManifest();
    return true;
}

// ==========================================
// 2. STORAGE STATUS
// ==========================================
StorageStatus DataBundleManager::getStorageStatus() {
    StorageStatus status = {0, 0, 0, false};

    // We use the driver wrapper because statvfs is unreliable in Arduino
    if (isMounted) {
        status.isDetected = true;
        uint64_t total = SD.totalBytes();
        uint64_t used = SD.usedBytes();
        
        status.totalKBytes = total / 1024;
        status.usedKBytes = used / 1024;
        status.freeKBytes = (total - used) / 1024;
    }
    return status;
}

// ==========================================
// 3. PURE C++ LOGIC (No Arduino libraries used here)
// ==========================================

bool DataBundleManager::startRecording(const std::string& sensorName, const std::string& date) {
    if (!isMounted || isRecording) return false;

    currentSensorName = sensorName;
    currentStartDate = date;
    
    // We use a static counter for filenames to avoid dependencies
    static unsigned long fileCounter = 0;
    fileCounter++;

    // IMPORTANT: The path must start with "/sd/" because that is where we mounted it
    char buf[128];
    snprintf(buf, sizeof(buf), "/sd/bundles/temp_%lu.csv", fileCounter);
    tempFilePath = std::string(buf);

    // Standard C Open
    FILE* f = fopen(tempFilePath.c_str(), "w");
    if (f == NULL) return false;

    fprintf(f, "Time,Part,Value\n");
    fclose(f);

    isRecording = true;
    return true;
}

bool DataBundleManager::logData(const std::string& time, const std::string& partName, const std::string& value) {
    if (!isRecording) return false;

    FILE* f = fopen(tempFilePath.c_str(), "a");
    if (f == NULL) return false;

    fprintf(f, "%s,%s,%s\n", time.c_str(), partName.c_str(), value.c_str());
    fclose(f);
    return true;
}

void DataBundleManager::stopAndSaveRecording() {
    if (!isRecording) return;

    // Create final filename
    static unsigned long saveCounter = 0;
    saveCounter++;
    
    char buf[128];
    snprintf(buf, sizeof(buf), "/sd/bundles/data_%lu.csv", saveCounter);
    std::string finalPath = std::string(buf);

    // Standard C Rename
    rename(tempFilePath.c_str(), finalPath.c_str());

    // Update RAM list
    BundleMetadata meta;
    meta.startDate = currentStartDate;
    meta.sensorName = currentSensorName;
    meta.filePath = finalPath;

    // FIFO Logic (Max 30)
    if (bundles.size() >= 30) {
        deleteBundle(0);
    }
    bundles.push_back(meta);
    saveManifest();

    isRecording = false;
}

void DataBundleManager::discardCurrentRecording() {
    if (!isRecording) return;
    remove(tempFilePath.c_str());
    isRecording = false;
}

// ==========================================
// 4. MANAGEMENT (Standard C++)
// ==========================================

void DataBundleManager::deleteBundle(int index) {
    if (index < 0 || index >= (int)bundles.size()) return;

    // Standard C Remove
    remove(bundles[index].filePath.c_str());
    bundles.erase(bundles.begin() + index);
    saveManifest();
}

void DataBundleManager::deleteAllBundles() {
    for (const auto& b : bundles) {
        remove(b.filePath.c_str());
    }
    bundles.clear();
    saveManifest();
}

int DataBundleManager::getBundleCount() {
    return (int)bundles.size();
}

std::vector<BundleMetadata> DataBundleManager::getBundlesForPage(int pageIndex) {
    std::vector<BundleMetadata> res;
    int start = pageIndex * 6; // 6 is MAX_BUNDLES_PER_PAGE
    
    if (start >= (int)bundles.size()) return res;

    for (int i = 0; i < 6; i++) {
        if (start + i < (int)bundles.size()) {
            res.push_back(bundles[start + i]);
        }
    }
    return res;
}

void DataBundleManager::saveManifest() {
    FILE* f = fopen("/sd/bundles/manifest.txt", "w");
    if (f == NULL) return;

    for (const auto& b : bundles) {
        fprintf(f, "%s|%s|%s\n", b.startDate.c_str(), b.sensorName.c_str(), b.filePath.c_str());
    }
    fclose(f);
}

void DataBundleManager::loadManifest() {
    bundles.clear();
    FILE* f = fopen("/sd/bundles/manifest.txt", "r");
    if (f == NULL) return;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        // Trim newlines manually
        size_t len = strlen(line);
        while(len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) {
            line[len-1] = '\0';
            len--;
        }
        if (len == 0) continue;

        std::vector<std::string> parts = splitString(line, '|');
        if (parts.size() == 3) {
            BundleMetadata m;
            m.startDate = parts[0];
            m.sensorName = parts[1];
            m.filePath = parts[2];
            bundles.push_back(m);
        }
    }
    fclose(f);
}

std::vector<std::string> DataBundleManager::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
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