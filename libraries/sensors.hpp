/**
 * @file sensors.hpp
 * @brief Declaration and implementation of sensor classes for sensor management using built-in exceptions.
 * 
 * These sensors are derived from the BaseSensor class and provide specific implementations for ADC, Joystick, DHT11, LinearHallAndDigital, PhotoResistor, and LinearHall sensors.
 * 
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny
 * 
 */

#ifndef SENSORS_HPP
#define SENSORS_HPP

/*********************
 *      INCLUDES
 *********************/
#include "base_sensor.hpp"  ///< BaseSensor class.

/**************************************************************************/
// SENSORS
/**************************************************************************/

/**
 * @class ADC
 * @brief ADC sensor class derived from BaseSensor.
 * 
 * Represents an Analog-to-Digital Converter (ADC) sensor. Implements initialization, configuration,
 * updating, and printing specific to ADC sensors.
 */
class ADC : public BaseSensor {
public:
    /**
     * @brief Constructs a new ADC object.
     * 
     * Initializes default values and sets the sensor type and description.
     * 
     * @param uid The unique sensor identifier.
     */
    ADC(std::string uid) : BaseSensor(uid)
    {
        init();
    }

    /**
     * @brief Virtual destructor.
     */
    virtual ~ADC() {}

    /**
     * @brief Initializes the sensor.
     * 
     * Additional initialization code can be added here.
     * 
     * @throws Exception if initialization fails.
     */
    virtual void init() override {
        // Additional initialization for sensor can be added here.
        Type = "ADC";
        Description = "Analog to Digital Converter";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("resolution", {"12", "bits", DataType::INT});
            // Default values
            addValueParameter("value", {"0", "", DataType::INT});
        }
        catch(const std::exception& e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     * 
     * This function draws the sensor.
     */
    virtual void draw() override {
        if (!redrawPenging)
        {
            return;
        }
        
        // Draw sensor

        // Call draw function here
        //TODO: Implement draw function
        
        redrawPenging = false; // Reset flag to redraw sensor.
    }

    /**
     * @brief Construct UI elements.
     * 
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override {
        // Construct sensor UI

        // Call construct LVGL functions here
    }
};


/**************************************************************************/

/**
 * @class Joystick
 * @brief Joystick sensor class derived from BaseSensor.
 * 
 * Represents a Joystick as a peripheral constructed as sensor. Implements initialization, configuration,
 * updating, and printing specific to Joystick sensors.
 */
class Joystick : public BaseSensor {
    public:
        /**
         * @brief Constructs a new Joystick object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        Joystick(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~Joystick() {}
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "Joystick";
            Description = "Joystick peripheral";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("resolution", {"8", "bits", DataType::INT});
                // Default values
                addValueParameter("XCoordination", {"50", "%", DataType::INT});
                addValueParameter("YCoordination", {"50", "%", DataType::INT});
                addValueParameter("Button", {"0", "ON/OFF", DataType::INT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            
            // Draw sensor
    
            // Call draw function here
            //TODO: Implement draw function
    
            
            redrawPenging = false; // Reset flag to redraw sensor.
        }
    };

    /**************************************************************************/

/**
 * @class DHT11
 * @brief DHT11 sensor class derived from BaseSensor.
 * 
 * Represents a DHT11 as a temperature and humidity sensor. Implements initialization, configuration,
 * updating, and printing specific to DHT11 sensors.
 */
class DHT11 : public BaseSensor {
    public:
        /**
         * @brief Constructs a new DHT11 object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        DHT11(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~DHT11() {}
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "DHT11";
            Description = "DHT11 Temperature & Humidity sensor";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("resolution", {"3", "digits", DataType::INT});
                // Default values
                addValueParameter("Temperature", {"0", "°C", DataType::INT});
                addValueParameter("Humidity", {"0", "%", DataType::INT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            
            // Draw sensor
    
            // Call draw function here
            //TODO: Implement draw function
    
            
            redrawPenging = false; // Reset flag to redraw sensor.
        }
    };

    /**************************************************************************/

/**
 * @class LinearHallAndDigital
 * @brief LinearHallAndDigital sensor class derived from BaseSensor.
 * 
 * Represents a Linear Hall sensor, which returns strenght of a magnet in gauss. Implements initialization, configuration,
 * updating, and printing specific to LinearHallAndDigital sensors.
 */
class LinearHallAndDigital : public BaseSensor {
    public:
        /**
         * @brief Constructs a new LinearHallAndDigital object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        LinearHallAndDigital(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~LinearHallAndDigital() {}
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "LinearHallAndDigital";
            Description = "Returns milliTesla of a measured magnet and if he goes past linearity";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("precision", {"2", "decimals", DataType::INT});
                // Default values
                addValueParameter("milliTesla Meter", {"0", "mT", DataType::FLOAT});
                addValueParameter("Magnet Detector", {"0", "", DataType::INT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            
            // Draw sensor
    
            // Call draw function here
            //TODO: Implement draw function
    
            
            redrawPenging = false; // Reset flag to redraw sensor.
        }
    };

        /**************************************************************************/

/**
 * @class PhotoResistor
 * @brief PhotoResistor sensor class derived from BaseSensor.
 * 
 * Represents a PhotoResistor which measures lux in users environment. Implements initialization, configuration,
 * updating, and printing specific to PhotoResistor sensors.
 */
class PhotoResistor : public BaseSensor {
    public:
        /**
         * @brief Constructs a new PhotoResistor object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        PhotoResistor(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~PhotoResistor() {}
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "PhotoResistor";
            Description = "Returns Lux of a measured environment, which users is in";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("resolution", {"5", "digits", DataType::INT});
                // Default values
                addValueParameter("Lux Meter", {"0", "Lux", DataType::INT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            
            // Draw sensor
    
            // Call draw function here
            //TODO: Implement draw function
    
            
            redrawPenging = false; // Reset flag to redraw sensor.
        }
    };

        /**************************************************************************/

/**
 * @class LinearHall
 * @brief LinearHall sensor class derived from BaseSensor.
 * 
 * Represents a Linear Hall sensor, which returns strenght of a magnet in gauss. Implements initialization, configuration,
 * updating, and printing specific to LinearHall sensors.
 */
class LinearHall : public BaseSensor {
    public:
        /**
         * @brief Constructs a new LinearHall object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        LinearHall(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~LinearHall() {}
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "LinearHall";
            Description = "Returns milliTesla of a measured magnet";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("precision", {"2", "decimals", DataType::INT});
                // Default values
                addValueParameter("milliTesla Meter", {"0", "milliTesla", DataType::FLOAT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            
            // Draw sensor
    
            // Call draw function here
            //TODO: Implement draw function
    
            
            redrawPenging = false; // Reset flag to redraw sensor.
        }
    };

            /**************************************************************************/

/**
 * @class DigitalTemperature
 * @brief DigitalTemperature sensor class derived from BaseSensor.
 * 
 * Represents a Temperature sensor, which returns °C and ON/OFF if the temperature goes past hardware-configured value. Implements initialization, configuration,
 * updating, and printing specific to DigitalTemperature sensors.
 */
class DigitalTemperature : public BaseSensor {
    public:
        /**
         * @brief Constructs a new DigitalTemperature object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        DigitalTemperature(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~DigitalTemperature() {}
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "DigitalTemperature";
            Description = "Returns temperature in °C and if the temperature goes past a hardware-configured value";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("precision", {"2", "decimals", DataType::INT});
                // Default values
                addValueParameter("Temperature", {"0", "°C", DataType::FLOAT});
                addValueParameter("Threshold", {"0", "ON/OFF", DataType::INT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            
            // Draw sensor
    
            // Call draw function here
            //TODO: Implement draw function
    
            
            redrawPenging = false; // Reset flag to redraw sensor.
        }
    };

                /**************************************************************************/

/**
 * @class AnalogTemperature
 * @brief AnalogTemperature sensor class derived from BaseSensor.
 * 
 * Represents a Temperature sensor, which returns °C. Implements initialization, configuration,
 * updating, and printing specific to AnalogTemperature sensors.
 */
class AnalogTemperature : public BaseSensor {
    public:
        /**
         * @brief Constructs a new AnalogTemperature object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        AnalogTemperature(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~AnalogTemperature() {}
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "AnalogTemperature";
            Description = "Returns temperature in °C";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("precision", {"2", "decimals", DataType::INT});
                // Default values
                addValueParameter("Temperature", {"0", "°C", DataType::FLOAT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            
            // Draw sensor
    
            // Call draw function here
            //TODO: Implement draw function
    
            
            redrawPenging = false; // Reset flag to redraw sensor.
        }
    };

    /**************************************************************************/

/**
 * @class TH
 * @brief Temperature/Huminidy sensor class derived from BaseSensor.
 * 
 * Represents a Temperature/Huminidy sensor. Implements initialization, configuration, updating, and printing
 * specific to Temperature/Huminidy sensors.
 */
class TH : public BaseSensor {
    public:
        /**
         * @brief Constructs a new TH object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        TH(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~TH() {}

    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "TH";
            Description = "Temperature & Humidity Sensor";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("precision", {"2", "decimals", DataType::INT});
                // Default values
                addValueParameter("temperature", {"0", "Celsia", DataType::FLOAT});
                addValueParameter("humidity", {"0", "%", DataType::INT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            // Draw sensor

            // Call draw function here
            //TODO: Implement draw function

            
            redrawPenging = false; // Reset flag to redraw sensor.
        }

        /**
         * @brief Construct UI elements.
         * 
         * This function constructs the sensor-specific GUI.
         */
        virtual void construct() override {
            // Construct sensor UI

            // Call construct LVGL functions here
        }
};

/**************************************************************************/
// DIGITAL SENSORS
/**************************************************************************/

/**
 * @class DigitalHall
 * @brief DigitalHall sensor class derived from BaseSensor.
 * 
 * Represents a Linear Hall sensor, which returns 1 if it in a presence of a magnet. Implements initialization, configuration,
 * updating, and printing specific to DigitalHall sensors.
 */
class DigitalHall : public BaseSensor {
    public:
        /**
         * @brief Constructs a new DigitalHall object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        DigitalHall(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~DigitalHall() {}
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "DigitalHall";
            Description = "Returns 1 of a measured magnet and if he goes past linearity";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("resolution", {"1", "bits", DataType::INT});
                // Default values
                addValueParameter("Magnet Detector", {"0", "", DataType::INT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            
            // Draw sensor
    
            // Call draw function here
            //TODO: Implement draw function
    
            
            redrawPenging = false; // Reset flag to redraw sensor.
        }
    };

        /**************************************************************************/

/**
 * @class PhotoInterrupter
 * @brief PhotoInterrupter sensor class derived from BaseSensor.
 * 
 * Represents a PhotoInterrupter, which returns 1 if something breaks line between IR light. Implements initialization, configuration,
 * updating, and printing specific to PhotoInterrupter sensors.
 */
class PhotoInterrupter : public BaseSensor {
    public:
        /**
         * @brief Constructs a new PhotoInterrupter object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        PhotoInterrupter(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~PhotoInterrupter() {}
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "PhotoInterrupter";
            Description = "Returns 1 of a measured magnet and if he goes past linearity";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("resolution", {"1", "bits", DataType::INT});
                // Default values
                addValueParameter("Motion Detector", {"0", "", DataType::INT});
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    
        /**
         * @brief Draw sensor.
         * 
         * This function draws the sensor.
         */
        virtual void draw() override {
            if (!redrawPenging)
            {
                return;
            }
            
            // Draw sensor
    
            // Call draw function here
            //TODO: Implement draw function
    
            
            redrawPenging = false; // Reset flag to redraw sensor.
        }
};

#endif //SENSORS_HPP