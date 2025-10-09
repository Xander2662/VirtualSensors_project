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

#include "../sensors/base_sensor.hpp"


/**
 * @class SensorManager
 * @brief Singleton class for managing sensors and their pin assignments.
 *
 * Provides methods for adding, accessing, synchronizing, and assigning sensors to pins.
 * Maintains a list of sensors and a mapping of sensors to hardware pins.
 */
class SensorManager {
public:

    /**
     * @brief Get the singleton instance of SensorManager
     * @return Reference to the SensorManager instance
     */
    static SensorManager& getInstance();

    /**
     * @brief Check if the manager has been initialized
     * @return True if initialized, false otherwise
     */
    bool isInitialized() const { return initialized; }

    // Deleted copy semantics to enforce singleton
    SensorManager(const SensorManager&) = delete;
    SensorManager& operator=(const SensorManager&) = delete;

    /**
     * @brief Set the initialized state
     * @param start True to set as initialized, false otherwise
     */
    void setInitialized(bool start);

    /**
     * @brief Initialize the manager and sensors
     * @param fromRequest If true, initialization is triggered by request
     */
    void init(bool fromRequest = false);

    /**
     * @brief Get a sensor by its unique ID
     * @param uid Unique identifier string
     * @return Pointer to the sensor, or nullptr if not found
     */
    BaseSensor* getSensor(std::string uid);

    /**
     * @brief Add a sensor to the manager
     * @param sensor Pointer to the sensor to add
     */
    void addSensor(BaseSensor* sensor);

    /**
     * @brief Synchronize a sensor by ID
     * @param id Unique identifier string
     */
    void sync(std::string id);

    /**
     * @brief Print information about a sensor by UID
     * @param uid Unique identifier string
     */
    void print(std::string uid);

    /**
     * @brief Print information about all sensors
     */
    void print();

    /**
     * @brief Resynchronize all sensors
     */
    void resync();

    /**
     * @brief Assign sensors to pins (bulk operation)
     */
    void assign();

    /**
     * @brief Erase all sensors and pin assignments
     */
    void erase();

    // --- Pin mapping ---

    static constexpr size_t NUM_PINS = 6; ///< Number of available pins for assignment

    /**
     * @brief Assign a sensor to the currently active pin
     * @param sensor Pointer to the sensor to assign
     */
    void assignSensorToPin(BaseSensor* sensor);

    /**
     * @brief Unassign the sensor from the currently active pin
     */
    void unassignSensorFromPin();

    /**
     * @brief Get the sensor assigned to a specific pin
     * @param pinIndex Index of the pin (0-based)
     * @return Pointer to the assigned sensor, or nullptr if none
     */
    BaseSensor* getAssignedSensor(size_t pinIndex) const;

    /**
     * @brief Get the currently selected sensor
     * @return Pointer to the current sensor
     */
    BaseSensor* getCurrentSensor();

    /**
     * @brief Assign a sensor and connect it to its pins
     * @param sensor Pointer to the sensor to assign and connect
     */
    void assignSensor(BaseSensor* sensor);

    /**
     * @brief Get read-only access to the list of sensors
     * @return Const reference to the vector of sensor pointers
     */
    const std::vector<BaseSensor*>& getSensors() const { return Sensors; }

    /**
     * @brief Get read-only access to the pin map
     * @return Const reference to the array of pin assignments
     */
    const std::array<BaseSensor*, NUM_PINS>& getPinMap() const { return PinMap; }

    /**
     * @brief Get access to the current sensor index
     * @return Reference to the current index
     */
    size_t& getCurrentIndex() { return currentIndex; }

    /**
     * @brief Set the active pin for assignment
     * @param pin Index of the pin to set as active
     */
    void setActivePin(size_t pin) { activePin = pin; }

    /**
     * @brief Reset the active pin to an invalid state
     */
    void resetActivePin() { activePin = NUM_PINS; }

private:
    /**
     * @brief Private constructor for singleton pattern
     */
    SensorManager();

    /**
     * @brief Destructor
     */
    ~SensorManager();

    std::array<BaseSensor*, NUM_PINS> PinMap; ///< Mapping of pins to sensors
    std::vector<BaseSensor*> Sensors;         ///< List of all managed sensors

    size_t currentIndex;                      ///< Index of the current sensor
    size_t activePin = NUM_PINS;              ///< Currently active pin for assignment

    bool initialized = false;                 ///< Initialization state flag
};

#endif // MANAGER_HPP 