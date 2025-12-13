/**
 * @file data_bundles.hpp
 * @brief bundles made from recording
 *
 * This header defines the mechanics for recording bundles of sensor data.
 *
 * @copyright 2025 MTA
 * @author Ondřej Wrubel
 */

#ifndef DATA_BUNDLE_MANAGER_H
#define DATA_BUNDLE_MANAGER_H

#pragma once

#include <vector>
#include <string>
#include <cstdio>
#include "data_bundle_types.hpp"

// Configuration
#define MOUNT_POINT "/sdcard"
#define MAX_TOTAL_BUNDLES 30
#define MAX_BUNDLES_PER_PAGE 6

class DataBundleManager {
private:
    std::vector<BundleMetadata> bundles;
    
    // Recording state
    bool isRecording;
    std::string tempFilePath;
    std::string currentSensorName;
    std::string currentStartDate;

    // Internal Helpers
    void saveManifest();
    void loadManifest();
    void appendToManifest(const BundleMetadata& meta);
    std::string generateUniqueFilename();
    std::vector<std::string> splitString(const std::string& str, char delimiter);

public:
    DataBundleManager();
    ~DataBundleManager();

    // Hardware Init (Mounts SD Card using ESP-IDF)
    bool initStorage();

    // Returns the card size and usage
    StorageStatus getStorageStatus();

    // Recording Controls
    // Returns true if started successfully
    bool startRecording(const std::string& sensorName, const std::string& date);
    
    // Appends a line to the active CSV
    bool logData(const std::string& time, const std::string& partName, const std::string& value);
    
    // Finalizes the file, adds to list, handles FIFO (30 max)
    void stopAndSaveRecording();
    
    // Deletes the temporary file
    void discardCurrentRecording();

    // Management
    int getBundleCount() const;
    std::vector<BundleMetadata> getBundlesForPage(int pageIndex);
    
    // Deletes specific bundle by global index
    void deleteBundle(int index);
    
    // Wipes everything
    void deleteAllBundles();

    // Loads heavy data for graphing
    std::vector<DataPoint> loadDataFromBundle(int index);
};

#endif