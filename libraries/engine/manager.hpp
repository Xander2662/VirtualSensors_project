/**
 * @file manager.hpp
 * @brief Declaration of the manager 
 * 
 * This header defines the manager class for managing sensors.
 * 
 * @copyright 2025 MTA
 * @author 
 * Ing. Jiri Konecny
 */
#ifndef __MANAGER_H_
#define __MANAGER_H_

/*********************
 *      INCLUDES
 *********************/
#include "sensor_factory.hpp"
#include "messenger.hpp"
#include "parser.hpp"
#include "helpers.hpp"

#include <vector>
#include <algorithm>

/**********************
 *      TYPEDEFS
 **********************/

/**
 * @class SensorManager
 * @brief Sensor manager class.
 * 
 * This class manages sensors. 
 * It provides functions to initialize, add, get, sync, print, redraw, and reconstruct sensors.
 */
class SensorManager
{
private:
    std::vector<BaseSensor*> Sensors;
public:

    /**
     * @brief Constructs a new SensorManager object.
     * 
     */
    SensorManager(/* args */)
    {
        Sensors = std::vector<BaseSensor*>();
    };

    ~ SensorManager(){};

    /**
     * @brief Initializes the sensor manager.
     * 
     * This function initializes the sensor manager by creating a list of sensors.
     * 
     * @param fromRequest Flag to indicate if the initialization is from a request.
     */
    void init(bool fromRequest = false){
        //Initialize messenger
        initMessenger();

        if(!fromRequest)
        {
            logMessage("Initializing manager via fixed sensors list...\n");
            createSensorList(Sensors);
            return;
        }

        //else
        logMessage("Initializing manager via request...\n");

        std::string request = "?INIT";
        sendMessage(request);
        std::string response = receiveMessage();
        //Check request format
        if(response.size() < 1 || response[0] != '?')
        {
            logMessage("Invalid sensor list format format!\n");
            init(false);
            return;
        }
        //Get rid of the '?' character
        response.erase(0, 1);

        createSensorList(Sensors, response); 
    }

    /**
     * @brief Retrieves a sensor by its unique identifier (UID).
     * 
     * This function searches through the list of sensors managed by the SensorManager
     * and returns the sensor that matches the given UID. If no sensor with the specified
     * UID is found, the function returns nullptr.
     * 
     * @param uid The unique identifier of the sensor to retrieve.
     * @return BaseSensor* A pointer to the sensor with the specified UID, or nullptr if not found.
     */
    BaseSensor* getSensor(std::string uid)
    {
        for (BaseSensor* sensor : Sensors)
        {
            if(sensor->UID == uid)
            {
                return sensor;
            }
        }
        return nullptr;
    }

    /**
     * @brief Adds a sensor to the sensor manager.
     * 
     * This function adds a sensor to the list of sensors managed by the SensorManager.
     * 
     * @param sensor The sensor to add.
     */
    void addSensor(BaseSensor* sensor)
    {
        if(sensor == nullptr)
        {
            return;
        }

        Sensors.push_back(sensor);
    }

    /**
     * @brief Synchronizes a sensor with the real sensor.
     * 
     * This function synchronizes the sensor with the real sensor by updating the sensor's values.
     * 
     * @param sensor The sensor to synchronize.
     */
    void sync(std::string id)
    {
        BaseSensor* sensor = getSensor(id);
        if(sensor != nullptr)
        {
            syncSensor(sensor);
        }
    }

    /**
     * @brief Prints a sensor.
     * 
     * This function prints the sensor informations with the specified UID.
     * 
     * @param uid The unique identifier of the sensor to print.
     */
    void print(std::string uid)
    {
        BaseSensor* sensor = getSensor(uid);
        printSensor(sensor);
    }

    /**
     * @brief Print all sensors.
     * 
     * This function prints all sensors managed by the SensorManager.
     */
    void print()
    {
        for (BaseSensor* sensor : Sensors)
        {
            printSensor(sensor);
        }
    }

    /**
     * @brief Redraws all sensors.
     * 
     * This function redraws all sensors managed by the SensorManager.
     */
    void redraw()
    {
        for (BaseSensor* sensor : Sensors)
        {
            drawSensor(sensor);
        }
    }

    /**
     * @brief Construct all sensors.
     * 
     * This function Construct all sensors managed by the SensorManager.
     */
    void reconstruct()
    {
        for (BaseSensor* sensor : Sensors)
        {
            constructSensor(sensor);
        }   
    }

    /**
     * @brief Resynchronizes all sensors.
     * 
     * This function resynchronizes all sensors managed by the SensorManager.
     */
    void resync()
    {
        /*
        for (BaseSensor* sensor : Sensors)
        {
            syncSensor(sensor);
        }
        */
       std::string request = "?UPDATE";
       sendMessage(request);

       std::string response = receiveMessage();
       std::vector<std::string> responses = splitString(response, '?');
       for(std::string resp : responses)
       {
           //logMessage("Response: %s\n", resp.c_str());
           SensorMetadata metadata = ParseMetadata(resp, CASE_SENSITIVE_SYNC);
           //logMessage("Metadata: %s\n", metadata.Data.c_str());
           if(CheckMetadata(&metadata))
           {
               //logMessage("Metadata is valid.\n");
               //logMessage("UID: %s\n", metadata.UID.c_str());
               //logMessage("Data: %s\n", metadata.Data.c_str());
               BaseSensor* sensor = getSensor(metadata.UID);
               if(sensor != nullptr)
               {
                   updateSensor(sensor, metadata.Data);
                   //printSensor(sensor);
               }
           }
       }
    } 
    
    /**
     * @brief Erases all sensors.
     * 
     * This function erases all sensors managed by the SensorManager.
     */
    void erase()
    {
        for (BaseSensor* sensor : Sensors)
        {
            delete sensor;
        }
        Sensors.clear();
    }
};


/*********************
 *      DECLARES
 *********************/


#endif //__MANAGER_H_