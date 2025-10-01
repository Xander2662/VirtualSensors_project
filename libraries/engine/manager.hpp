/**
 * @file manager.hpp
 * @brief Declaration of the manager
 *
 * This header defines the manager class for managing sensors.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */
#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include <cstddef>
#include <string>
#include <array>

class BaseSensor;

class SensorManager {
public:

    // Singleton accessor
    static SensorManager& getInstance();

    //Init checker for ui.ino
    bool isInitialized() const { return initialized; }
    // Deleted copy semantics
    SensorManager(const SensorManager&) = delete;
    SensorManager& operator=(const SensorManager&) = delete;

    void setInitialized(bool start);
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

    // Pin mapping
    static constexpr size_t NUM_PINS = 6;
    //void assignSensorToPin(size_t pinIndex, BaseSensor* sensor);
    void assignSensorToPin(BaseSensor* sensor);
    BaseSensor* getAssignedSensor(size_t pinIndex) const; 
    //BaseSensor* getCurrentSensor();
    void sendPinsOnSerial() const;
    
    // read-only access to sensor list
    const std::vector<BaseSensor*>& getSensors() const { return Sensors; }
    const std::array<BaseSensor*, NUM_PINS>& getPinMap() const { return PinMap; }
    // access to currentIndex
    size_t& getCurrentIndex() { return currentIndex; }
    //void setCurrentIndex(size_t index) { currentIndex = index; }
    void setActivePin(size_t pin) { activePin = pin; }
    void resetActivePin() { activePin = NUM_PINS; }
    //const size_t getActivePin() const { return activePin; }

private:
    SensorManager();
    ~SensorManager();

    std::array<BaseSensor*, NUM_PINS> PinMap;
    std::vector<BaseSensor*> Sensors;

    size_t currentIndex;
    size_t activePin = NUM_PINS;

    //the init checker variable
    bool initialized = false;
};

#endif // MANAGER_HPP 