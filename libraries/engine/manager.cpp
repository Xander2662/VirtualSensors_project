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
#include "sensor_factory.hpp"
#include "messenger.hpp"
#include "parser.hpp"
#include "helpers.hpp"
#include "base_sensor.hpp"

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

/*BaseSensor* SensorManager::getCurrentSensor()
{
    if (currentIndex < Sensors.size())
    {
        return Sensors[currentIndex];
    }
    return nullptr;
}*/


void SensorManager::addSensor(BaseSensor* sensor) {
    if (sensor) Sensors.push_back(sensor);
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
    for (auto* sensor : Sensors) printSensor(sensor);
}

void SensorManager::redraw() {
    for (auto* sensor : Sensors) drawSensor(sensor);
}

void SensorManager::reconstruct() {
    for (auto* sensor : Sensors) constructSensor(sensor);
}

void SensorManager::resync() {
    std::string request = "?UPDATE";
    sendMessage(request);
    std::string response = receiveMessage();
    auto responses = splitString(response, '?');
    for (auto& resp : responses) {
        auto metadata = ParseMetadata(resp, CASE_SENSITIVE_SYNC);
        if (CheckMetadata(&metadata)) {
            BaseSensor* sensor = getSensor(metadata.UID);
            if (sensor) updateSensor(sensor, metadata.Data);
        }
    }
}

void SensorManager::erase() {
    for (auto* sensor : Sensors) delete sensor;
    Sensors.clear();
}

/////////////////////////
// pin management
/////////////////////////

/*void SensorManager::assignSensorToPin(size_t pinIndex, BaseSensor* sensor) {
    if (pinIndex >= NUM_PINS) return;
    PinMap[pinIndex] = sensor;
}*/
void SensorManager::assignSensorToPin(BaseSensor* sensor) {
    if (activePin > NUM_PINS) return;
    PinMap[activePin] = sensor;
}


BaseSensor* SensorManager::getAssignedSensor(size_t pinIndex) const {
    if (pinIndex > NUM_PINS) return nullptr;
    return PinMap[pinIndex];
}

//NEED TO CHANGE THE OUTPUT
void SensorManager::sendPinsOnSerial() const {
    std::ostringstream ss;
    ss << "?PINS:";
    for (size_t i = 0; i < NUM_PINS; ++i) {
        const BaseSensor* s = PinMap[i];
        if (s) ss << i << "=" << s->UID;
        else ss << i << "=UNUSED";
        if (i + 1 < NUM_PINS) ss << "&";
    }
    std::string out = ss.str();
    logMessage(out.c_str());

}

void SensorManager::showCurrentSensorInfo(bool isVisualisation) const
{
    BaseSensor* sensor = nullptr;

    if (!isVisualisation) {
        if (currentIndex < Sensors.size())
            sensor = Sensors[currentIndex];
    } else {
        if (currentIndex < PinMap.size())
            sensor = PinMap[currentIndex];
    }

    if (!sensor) {
        logMessage("No sensor selected.\n");
        return;
    }

    logMessage("Sensor: %s\n", sensor->Type.c_str());
    logMessage("Description: %s\n", sensor->Description.c_str());
}