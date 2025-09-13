/**
 * @file manager_shim.cpp
 * @brief Globalizing instances of functions
 *
 * @copyright 2025 MTA
 * @author Ondřej Wrubel
 */

#include "manager.hpp"
#include "base_sensor.hpp"
extern "C" void vs_nextSensor(bool isVisualisation) {
    SensorManager::getInstance().nextSensor(isVisualisation);
}

extern "C" void vs_prevSensor(bool isVisualisation) {
    SensorManager::getInstance().prevSensor(isVisualisation);
}   

extern "C" void vs_confirmSensor() {
    SensorManager::getInstance().confirmSensor();
}   

extern "C" void vs_goBack() {
    SensorManager::getInstance().goBack();
}   
