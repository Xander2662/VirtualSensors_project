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

    // Public API
    void hideAllExceptFirst(bool isVisualisation = true);
    void nextSensor(bool isVisualisation);
    void prevSensor(bool isVisualisation);
    void confirmSensor();
    void goBack();

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
    //So that it can be used externally
    //void assignSensorToPin(size_t pinIndex, BaseSensor* sensor);
    //Internal version with activePin.
    void assignSensorToPin(BaseSensor* sensor);
    BaseSensor* getAssignedSensor(size_t pinIndex) const;
    void setActivePin(size_t pin) { activePin = pin; }


    // send current mapping on serial
    void sendPinsOnSerial() const;

    // read-only access to sensor list
    //const std::vector<BaseSensor*>& getSensors() const { return Sensors; }

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