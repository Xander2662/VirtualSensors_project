/**
 * @file data_bundle_manager.hpp
 * @brief bundles made from recording
 *
 * This header defines the manager for data bundles recorded from sensors.
 *
 * @copyright 2025 MTA
 * @author Ondřej Wrubel
 */

#ifndef DATA_BUNDLE_MANAGER_H
#define DATA_BUNDLE_MANAGER_H

#include <vector>
#include <string>
#include <cstdio>

// Standard C++ Structures
struct BundleMetadata {
    std::string startDate;
    std::string sensorName;
    std::string filePath;
};

struct StorageStatus {
    uint64_t totalKBytes;
    uint64_t usedKBytes;
    uint64_t freeKBytes;
    bool isDetected;
};

class DataBundleManager {
private:
    std::vector<BundleMetadata> bundles;
    bool isMounted;
    bool isRecording;
    
    std::string tempFilePath;
    std::string currentSensorName;
    std::string currentStartDate;

    void saveManifest();
    void loadManifest();
    std::vector<std::string> splitString(const std::string& str, char delimiter);

public:
    DataBundleManager();
    
    // Hardware Init
    bool initStorage(); 

    // Pure C++ Recording Logic
    bool startRecording(const std::string& sensorName, const std::string& date);
    bool logData(const std::string& time, const std::string& partName, const std::string& value);
    void stopAndSaveRecording();
    void discardCurrentRecording();

    // Management
    void deleteBundle(int index);
    void deleteAllBundles();
    int getBundleCount();
    std::vector<BundleMetadata> getBundlesForPage(int pageIndex);
    StorageStatus getStorageStatus();
};

#endif