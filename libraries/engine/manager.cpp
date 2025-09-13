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
#include "main_menu.hpp"

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

//the isVisualisation makes sure that the proper version of construct is made
void SensorManager::hideAllExceptFirst(bool isVisualisation) {
    if (!isVisualisation) {
        for (auto* s : Sensors) {
            constructSensor(s, false);
        }
        for (size_t i = 1; i < Sensors.size(); ++i) {
            Sensors[i]->hide();
        }
        if (!Sensors.empty()) {
            Sensors[0]->show();
            currentIndex = 0;
        }
    } else {
        for (auto* s : PinMap) {
            constructSensor(s, true);
        }
        for (size_t i = 1; i < PinMap.size(); ++i) {
            if (PinMap[i]) PinMap[i]->hide();
        }
        if (PinMap[0]) {
            PinMap[0]->show();
            currentIndex = 0;
        }
    }
}
void SensorManager::nextSensor(bool isVisualisation) {
    if (isVisualisation) {
        if (Sensors.empty()) return;
        Sensors[currentIndex]->hide();
        currentIndex = (currentIndex + 1) % Sensors.size();
        Sensors[currentIndex]->show();
    } else {
        if (PinMap.empty()) return;
        size_t count = 0;
        for (auto* s : PinMap) if (s) count++;
        if (count == 0) return;

        // Find next valid pin
        PinMap[currentIndex]->hide();
        do {
            currentIndex = (currentIndex + 1) % PinMap.size();
        } while (!PinMap[currentIndex]);
        PinMap[currentIndex]->show();
    }
}

void SensorManager::prevSensor(bool isVisualisation) {
    if (isVisualisation) {
        if (Sensors.empty()) return;
        Sensors[currentIndex]->hide();
        currentIndex = (currentIndex + Sensors.size() - 1) % Sensors.size();
        Sensors[currentIndex]->show();
    } else {
        if (PinMap.empty()) return;
        size_t count = 0;
        for (auto* s : PinMap) if (s) count++;
        if (count == 0) return;

        // Find previous valid pin
        PinMap[currentIndex]->hide();
        do {
            currentIndex = (currentIndex + PinMap.size() - 1) % PinMap.size();
        } while (!PinMap[currentIndex]);
        PinMap[currentIndex]->show();
    }
}

void SensorManager::confirmSensor() {
    if (Sensors.empty()) return;
    assignSensorToPin(Sensors[currentIndex]);
    sendPinsOnSerial();
    MainMenu::getInstance().update_pin_label_text(activePin);
    goBack();
}

void SensorManager::goBack() {
    if (Sensors.empty()) {
        return;
    }

    Sensors[currentIndex]->hide();
    PinMap[currentIndex]->hide();

    currentIndex = 0;
    activePin = NUM_PINS;
    initialized = false;


    MainMenu::getInstance().show();
}

void SensorManager::setInitialized(bool start){
    initialized = start;
}

void SensorManager::init(bool fromRequest) {
    initMessenger();
    initialized = true;

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