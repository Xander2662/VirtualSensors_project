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

bool configSensor(BaseSensor *sensor, const std::string &config) {
    if(sensor == nullptr) {
        return false;
    }
    sensor->setError(nullptr); // Clear error if config successful

    try {
        std::unordered_map<std::string, std::string> params = parseParamsFromString(config, CASE_SENSITIVE);
        sensor->config(params);
        return true;
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return false;
    }
    catch (const std::exception &e)
    {
        logMessage("Standard exception during synchronization: %s\n", e.what());
        sensor->setError(new Exception(e));
        return false;
    }
    catch(...)
    {
        logMessage("Unknown exception during synchronization!\n");
        sensor->setError(new Exception("configSensor","Unknown exception during synchronization!"));
        return false;
    }
}


bool updateSensor(BaseSensor *sensor, const std::string &update) {
    if(sensor == nullptr) {
        return false;
    }
    sensor->setError(nullptr); // Clear error if config successful

    try {
        std::unordered_map<std::string, std::string> params = parseParamsFromString(update, CASE_SENSITIVE);
        sensor->update(params);
        return true;   
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return false;
    }
    catch (const std::exception &e)
    {
        logMessage("Standard exception during synchronization: %s\n", e.what());
        sensor->setError(new Exception(e));
        return false;
    }
    catch(...)
    {
        logMessage("Unknown exception during synchronization!\n");
        sensor->setError(new Exception("updateSensor","Unknown exception during synchronization!"));
        return false;
    }
}

void printSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return;
    }
    sensor->setError(nullptr); // Clear error if config successful
    
    try {
        sensor->print();
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return;
    }
    catch (const std::exception &e)
    {
        logMessage("Standard exception during synchronization: %s\n", e.what());
        sensor->setError(new Exception(e));
        return;
    }
    catch(...)
    {
        logMessage("Unknown exception during synchronization!\n");
        sensor->setError(new Exception("printSensor","Unknown exception during synchronization!"));
        return;
    }
}

bool syncSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return false;
    }
    sensor->setError(nullptr); // Clear error if config successful

    try {
        return sensor->synchronize();
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return false;
    }
    catch (const std::exception &e)
    {
        logMessage("Standard exception during synchronization: %s\n", e.what());
        sensor->setError(new Exception(e));
        return false;
    }
    catch(...)
    {
        logMessage("Unknown exception during synchronization!\n");
        sensor->setError(new Exception("syncSensor","Unknown exception during synchronization!"));
        return false;
    }
}

bool initSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return false;
    }
    sensor->setError(nullptr); // Clear error if config successful

    try {
        sensor->init();
        return true;
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return false;
    }
    catch (const std::exception &e)
    {
        logMessage("Standard exception during synchronization: %s\n", e.what());
        sensor->setError(new Exception(e));
        return false;
    }
    catch(...)
    {
        logMessage("Unknown exception during synchronization!\n");
        sensor->setError(new Exception("initSensor","Unknown exception during synchronization!"));
        return false;
    }
}

bool connectSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return false;
    }
    sensor->setError(nullptr); // Clear error if config successful

    if(sensor->getPins().empty()) {
        return false; // No pins assigned, nothing to connect
    }

    try {
        if (disconnectSensor(sensor)) // Disconnect first;
        {
            return sensor->connect();
        }    
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return false;
    }
    catch (const std::exception &e)
    {
        logMessage("Standard exception during synchronization: %s\n", e.what());
        sensor->setError(new Exception(e));
        return false;
    }
    catch(...)
    {
        logMessage("Unknown exception during synchronization!\n");
        sensor->setError(new Exception("connectSensor","Unknown exception during synchronization!"));
        return false;
    }
}

bool disconnectSensor(BaseSensor *sensor) {
    if(sensor == nullptr) {
        return false;
    }
    sensor->setError(nullptr); // Clear error if config successful

    if(sensor->getPins().empty()) {
        return true; // No pins assigned, nothing to disconnect
    }

    try {
        return sensor->disconnect();
    } catch (const Exception &ex) {
        ex.print();
        sensor->setError(new Exception(ex));
        return false;
    }
    catch (const std::exception &e)
    {
        logMessage("Standard exception during synchronization: %s\n", e.what());
        sensor->setError(new Exception(e));
        return false;
    }
    catch(...)
    {
        logMessage("Unknown exception during synchronization!\n");
        sensor->setError(new Exception("disconnectSensor","Unknown exception during synchronization!"));
        return false;
    }
}


