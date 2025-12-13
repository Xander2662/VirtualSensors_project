#pragma once
#include <string>
#include <vector>

// Metadata for each data bundle
struct BundleMetadata {
    std::string startDate;   // "YYYY-MM-DD"
    std::string sensorName;  // "DHT11"
    std::string filePath;    // "/sdcard/data_12345.csv"
};

// Used only when loading specific data for a chart
struct DataPoint {
    std::string time;      // "hh:mm:ss"
    std::string partName;  // "Temperature"
    std::string value;     // "24.5"
};

struct StorageStatus {
    uint64_t totalKBytes; // Total size in KB
    uint64_t usedKBytes;  // Used size in KB
    uint64_t freeKBytes;  // Free size in KB
    bool isDetected;      // True if card is inserted and mounted
};