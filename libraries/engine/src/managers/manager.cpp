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

void SensorManager::setInitialized(bool start){
    initialized = start;
}

void SensorManager::init(bool fromRequest) {
    initMessenger();

    if (!fromRequest) {
        logMessage("Initializing manager via fixed sensors list...\n");
        createSensorList(Sensors);
        return;
    }
    logMessage("Initializing manager via request...\n");
    std::string request = "?INIT";
    sendMessage(request);
    std::string response = receiveMessage();
    if (response.empty() || response[0] != '?') {
        logMessage("Invalid sensor list format!\n");
        init(false);
        return;
    }
    response.erase(0, 1);
    createSensorList(Sensors, response);
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
    if (sensor == nullptr) {
        return;
    }
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
    if (activePin > NUM_PINS) return;

    PinMap[activePin] = sensor;
    sensor->assignPin(std::to_string(activePin));
    logMessage("Sensor %s assigned to pin %zu\n", sensor->UID.c_str(), activePin);
}

void SensorManager::unassignSensorFromPin() {
    if (activePin > NUM_PINS) return;

    BaseSensor* sensor = PinMap[activePin];
    PinMap[activePin] = nullptr;
    sensor->unassignPin(std::to_string(activePin));
    logMessage("Sensor %s unassigned from pin %zu\n", sensor->UID.c_str(), activePin);
}


BaseSensor* SensorManager::getAssignedSensor(size_t pinIndex) const {
    if (pinIndex > NUM_PINS) return nullptr;
    return PinMap[pinIndex];
}