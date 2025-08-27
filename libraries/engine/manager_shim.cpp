#include "manager.hpp"

extern "C" void vs_nextSensor() {
    SensorManager::getInstance().nextSensor();
}

extern "C" void vs_prevSensor() {
    SensorManager::getInstance().prevSensor();
}