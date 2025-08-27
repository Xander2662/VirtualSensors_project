/**
 * @file manager.cpp
 * @brief Definition of the manager 
 * 
 * This source defines the manager functions and implementations.
 * 
 * @copyright 2025 MTA
 * @author 
 * Ing. Jiri Konecny
 */

/*********************
 *      INCLUDES
 *********************/
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

SensorManager::SensorManager()
 : Sensors(), currentIndex(0)
{
}

SensorManager::~SensorManager() {
    for (auto* s : Sensors) delete s;
}

void SensorManager::hideAllExceptFirst() {
    for (auto* s : Sensors) {
        constructSensor(s);
    }
    for (size_t i = 1; i < Sensors.size(); ++i) {
        Sensors[i]->hide();
    }
    if (!Sensors.empty()) {
        Sensors[0]->show();
        currentIndex = 0;
    }
}

void SensorManager::nextSensor() {
    if (Sensors.empty()) {
        return;
    }
    Sensors[currentIndex]->hide();
    currentIndex = (currentIndex + 1) % Sensors.size();
    Sensors[currentIndex]->show();
}

void SensorManager::prevSensor() {
    if (Sensors.empty()) {
        return;
    }
    Sensors[currentIndex]->hide();
    currentIndex = (currentIndex + Sensors.size() - 1) % Sensors.size();
    Sensors[currentIndex]->show();
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