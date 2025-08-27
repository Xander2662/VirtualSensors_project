/**
 * @file manager.hpp
 * @brief Declaration of the manager
 *
 * This header defines the manager class for managing sensors.
 *
 * @copyright 2025 MTA
 * @author
 * Ing. Jiri Konecny
 */
#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include <cstddef>
#include <string>

class BaseSensor;

class SensorManager {
public:
    // Singleton accessor
    static SensorManager& getInstance();

    // Deleted copy semantics
    SensorManager(const SensorManager&) = delete;
    SensorManager& operator=(const SensorManager&) = delete;

    // Public API
    void hideAllExceptFirst();
    void nextSensor();
    void prevSensor();

    void init(bool fromRequest = false);

    BaseSensor* getSensor(std::string uid);
    void addSensor(BaseSensor* sensor);
    void sync(std::string id);
    void print(std::string uid);
    void print();
    void redraw();
    void reconstruct();
    void resync();
    void erase();

private:
    SensorManager();
    ~SensorManager();

    std::vector<BaseSensor*> Sensors;
    size_t currentIndex;
};

#endif // MANAGER_HPP