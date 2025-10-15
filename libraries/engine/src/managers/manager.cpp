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

SensorManager::SensorManager() : Sensors(), currentIndex(0) {
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

        logMessage("\tinitializing of protocol...\n");
        auto response = Protocol::init_dummy();
        if (response.status == ResponseStatusEnum::ERROR)
        {
            throw SensorInitializationFailException("SensorManager::init", response.error, ErrorCode::CRITICAL_ERROR_CODE);
        }
        logMessage("\tdone!\n");
    }
    catch(const Exception &e)
    {
        e.print();
        Status = ManagerStatus::ERROR;;
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
    resetPinMap();
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
        auto response = Protocol::init(app, db);
        if (response.status == ResponseStatusEnum::ERROR)
        {
            throw SensorInitializationFailException("SensorManager::init", response.error, ErrorCode::CRITICAL_ERROR_CODE);
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
    resetPinMap();
    logMessage("Initialization done!\n");
    return initialized = true;
}

void SensorManager::resetPinMap() {
    for (size_t i = 0; i < NUM_PINS; ++i) {
        PinMap[i].pinNumber = i;
        PinMap[i].locked = false;

        PinMap[i].unassignSensor();
    }
}

BaseSensor* SensorManager::getCurrentSensor()
{
    if (currentIndex < PinMap.size())
    {
        return PinMap[currentIndex].assignedSensor;
    }
    return nullptr;
}

BaseSensor* SensorManager::getSensor(std::string uid) {
    for (auto* sensor : Sensors) {
        if (sensor->UID == uid) return sensor;
    }
    return nullptr;
}

void SensorManager::addSensor(BaseSensor* sensor) {
    if (sensor) Sensors.push_back(sensor);
}

bool SensorManager::sync(std::string id) {
    BaseSensor* sensor = getSensor(id);
    if (sensor) return syncSensor(sensor);

    return false;
}

void SensorManager::print(std::string uid) {
    BaseSensor* sensor = getSensor(uid);
    printSensor(sensor);
}

void SensorManager::print() {
    BaseSensor* currentSensor = getCurrentSensor();
    printSensor(currentSensor);
}

bool SensorManager::resync() 
{
    if(!isRunning()) return false;

    BaseSensor* currentSensor = getCurrentSensor();
    return syncSensor(currentSensor);
}

bool SensorManager::connect() 
{
    bool result = true;
    for (auto virtualPin : PinMap) {
        if(virtualPin.assignedSensor) {
            result &= connectSensor(virtualPin.assignedSensor);
        }
    }
    return result;
}

void SensorManager::erase() {
    resetPinMap();
    currentIndex = 0;
    for (auto* sensor : Sensors) delete sensor;
    Sensors.clear();
}

/////////////////////////
// Pin management
/////////////////////////

bool SensorManager::assignSensorToPin(BaseSensor* sensor, int activePin) {
    if (activePin >= NUM_PINS) return false;

    return PinMap[activePin].assignSensor(sensor);
}

bool SensorManager::unassignSensorFromPin(int activePin) {
    if (activePin >= NUM_PINS) return false;

    PinMap[activePin].unassignSensor();
}

BaseSensor* SensorManager::getAssignedSensor(size_t pinIndex) const {
    if (pinIndex >= NUM_PINS) return nullptr;
    return PinMap[pinIndex].assignedSensor;
}

int SensorManager::getPinNumber(size_t pinIndex) const {
    if (pinIndex >= NUM_PINS) return -1;
    return PinMap[pinIndex].pinNumber;
}

bool SensorManager::isPinAvailable(size_t pinIndex) const {
    if (pinIndex >= NUM_PINS) return false;
    return PinMap[pinIndex].isAvailable();
}

bool SensorManager::isPinLocked(size_t pinIndex) const {
    if (pinIndex >= NUM_PINS) return false;
    return PinMap[pinIndex].isLocked();
}