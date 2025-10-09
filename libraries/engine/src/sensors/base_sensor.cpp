/**
 * @file base_sensor.cpp
 * @brief Implementation of sensor management functions.
 * 
 * This file implements sensor functionalities, including the factory function for creating
 * sensors instances. The factory function dynamically allocates an sensor, calls its
 * initialization method, and returns a pointer. If initialization fails, it logs the error,
 * cleans up, and rethrows the exception.
 * 
 * @copyright 2024 MTA
 * @author Ing. Jiri Konecny
 * 
 */

#include "base_sensor.hpp"

/*Global functions*/


/*Create functions*/
//implemented in header file as generic function

/*General functions*/

void configSensor(BaseSensor *sensor, const std::string &config) {
    if(sensor == nullptr) {
        return;
    }

    try {
        std::unordered_map<std::string, std::string> params = parseParamsFromString(config, CASE_SENSITIVE);
        sensor->config(params);
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return;
    }

    sensor->setError(nullptr); // Clear error if config successful
}


void updateSensor(BaseSensor *sensor, const std::string &update) {
    if(sensor == nullptr) {
        return;
    }

    try {
        std::unordered_map<std::string, std::string> params = parseParamsFromString(update, CASE_SENSITIVE);
        sensor->update(params);
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return;
    }

    sensor->setError(nullptr); // Clear error if config successful
}

void printSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return;
    }
    
    try {
        sensor->print();
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return;
    }

    sensor->setError(nullptr); // Clear error if config successful
}

void syncSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return;
    }

    try {
        sensor->synchronize();
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return;
    }

    sensor->setError(nullptr); // Clear error if config successful
}

void initSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return;
    }

    try {
        sensor->init();
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return;
    }

    sensor->setError(nullptr); // Clear error if config successful
}

void connectSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return;
    }

    try {
        disconnectSensor(sensor); // Disconnect first
        sensor->connect();
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return;
    }

    sensor->setError(nullptr); // Clear error if config successful
}

void disconnectSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return;
    }

    try {
        sensor->disconnect();
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return;
    }

    sensor->setError(nullptr); // Clear error if config successful
}


