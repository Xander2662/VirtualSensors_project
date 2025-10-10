/**
 * @file manager.cpp
 * @brief Definition of the manager 
 * 
 * This source defines the manager functions and implementations.
 * 
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */

/*********************
 *      INCLUDES
 *********************/

#include <sstream>
#include "manager.hpp"
#include "../sensors/sensor_factory.hpp"
#include "helpers.hpp"

SensorManager& SensorManager::getInstance() {
    static SensorManager instance;
    return instance;
}

SensorManager::SensorManager() : Sensors(), currentIndex(0) {
    PinMap.fill(nullptr);
}

SensorManager::~SensorManager() {
    for (auto* s : Sensors) delete s;
}

bool SensorManager::init() {
    initialized = false;
    try
    {
        initMessenger();

        logMessage("Initializing manager via fixed sensors list...\n");
        createSensorList(Sensors);

        logMessage("Initializing of protocol...\n");
        if (!Protocol::init_dummy()) {
            throw SensorInitializationFailException("SensorManager::init", "Protocol initialization failed", ErrorCode::CRITICAL_ERROR_CODE);
        }
    }
    catch(const Exception &e)
    {
        e.print();
        Status = ManagerStatus::ERROR;
        return false;
    }
    catch (const std::exception &e)
    {
        logMessage("Standard exception during initialization: %s\n", e.what());
        Status = ManagerStatus::ERROR;
        return false;
    }
    catch(...)
    {
        logMessage("Unknown exception during initialization!\n");
        Status = ManagerStatus::ERROR;
        return false;
    }


    Status = ManagerStatus::READY;
    currentIndex = 0;
    activePin = NUM_PINS; // no active pin
    logMessage("Initialization done!\n");
    return initialized = true;
}

bool SensorManager::init(std::string configFile) {
    initialized = false;
    try
    {
        initMessenger();

        logMessage("Initializing manager via configuration file: %s\n", configFile.c_str());
        //Init from config file here
        throw Exception("SensorManager::init", "Initialization from config file not implemented yet", ErrorCode::NOT_DEFINED_ERROR);

        std::string app = "VirtualSensors 1.0"; //Get from config?
        std::string db = "1.0"; //Get from config?
        logMessage("Initializing of protocol...\n");
        if (!Protocol::init(app, db)) {
            throw SensorInitializationFailException("SensorManager::init", "Protocol initialization failed", ErrorCode::CRITICAL_ERROR_CODE);
        }
    }
    catch(const Exception &e)
    {
        e.print();
        Status = ManagerStatus::ERROR;
        return false;
    }
    catch (const std::exception &e)
    {
        logMessage("Standard exception during initialization: %s\n", e.what());
        Status = ManagerStatus::ERROR;
        return false;
    }
    catch(...)
    {
        logMessage("Unknown exception during initialization!\n");
        Status = ManagerStatus::ERROR;
        return false;
    }
    
    Status = ManagerStatus::READY;
    currentIndex = 0;
    activePin = NUM_PINS; // no active pin
    logMessage("Initialization done!\n");
    return initialized = true;
}

BaseSensor* SensorManager::getSensor(std::string uid) {
    for (auto* sensor : Sensors) {
        if (sensor->UID == uid) return sensor;
    }
    return nullptr;
}

BaseSensor* SensorManager::getCurrentSensor()
{
    if (currentIndex < Sensors.size())
    {
        return Sensors[currentIndex];
    }
    return nullptr;
}

void SensorManager::addSensor(BaseSensor* sensor) {
    if (sensor) Sensors.push_back(sensor);
}

void SensorManager::assignSensor(BaseSensor* sensor) {
    connectSensor(sensor);
}

void SensorManager::sync(std::string id) {
    BaseSensor* sensor = getSensor(id);
    if (sensor) syncSensor(sensor);
}

void SensorManager::print(std::string uid) {
    BaseSensor* sensor = getSensor(uid);
    printSensor(sensor);
}

void SensorManager::print() {
    BaseSensor* currentSensor = getCurrentSensor();
    printSensor(currentSensor);
}

void SensorManager::resync() 
{
    BaseSensor* currentSensor = getCurrentSensor();
    syncSensor(currentSensor);
}

void SensorManager::assign() 
{
    for (auto* sensor : Sensors) connectSensor(sensor);
}

void SensorManager::erase() {
    for (auto* sensor : Sensors) delete sensor;
    Sensors.clear();
}

/////////////////////////
// pin management
/////////////////////////

void SensorManager::assignSensorToPin(BaseSensor* sensor) {
    if (activePin >= NUM_PINS) return;

    try
    {
        PinMap[activePin] = sensor;
        sensor->assignPin(std::to_string(activePin));
        logMessage("Sensor %s assigned to pin %zu\n", sensor->UID.c_str(), activePin);
    }
    catch(const std::exception& e)
    {
        logMessage("Error assigning sensor to pin: %s\n", e.what());
        return;
    }
}

void SensorManager::unassignSensorFromPin() {
    if (activePin >= NUM_PINS) return;

    try
    {
        BaseSensor* sensor = PinMap[activePin];
        PinMap[activePin] = nullptr;
        
        sensor->unassignPin(std::to_string(activePin));
        logMessage("Sensor %s unassigned from pin %zu\n", sensor->UID.c_str(), activePin);
    }
    catch(const std::exception& e)
    {
        logMessage("Error unassigning sensor from pin: %s\n", e.what());
    }
}


BaseSensor* SensorManager::getAssignedSensor(size_t pinIndex) const {
    if (pinIndex >= NUM_PINS) return nullptr;
    return PinMap[pinIndex];
}