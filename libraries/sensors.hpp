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

 extern "C" {
    #include "lvgl.h"
    }
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
/**************************************************************************/
// I2C
/**************************************************************************/
/**************************************************************************/
/**
 * @class TP
 * @brief Temperature/Pressure sensor class derived from BaseSensor.
 * 
 * Represents a Temperature/Pressure sensor. Implements initialization, configuration, updating, and printing
 * specific to Temperature/Pressure sensors.
 */

 class TP : public BaseSensor {
    public:
        /**
         * @brief Constructs a new TP object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        TP(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~TP() {}
        lv_obj_t* ui_Label1;
        lv_obj_t* ui_temp;
        lv_obj_t* ui_pres;
        lv_obj_t * ui_Panel3;

    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "TP";
            Description = "Temperature & Pressure Sensor";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("Precision", {"2", "decimals", DataType::INT});
                // Default values
                addValueParameter("Temperature", {"0", "°C", DataType::FLOAT});
                addValueParameter("Pressure", {"0", "hPa", DataType::FLOAT});
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
            lv_label_set_text(ui_pres,"0 hPa");
            lv_label_set_text(ui_temp,"Temp: 0 °C");
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
        
        
    ui_Panel3= lv_obj_create(lv_scr_act());
    lv_obj_set_width(ui_Panel3, 140);
    lv_obj_set_height(ui_Panel3, 190);
    lv_obj_set_align(ui_Panel3, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel3, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(ui_Panel3, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_Panel3, LV_OBJ_FLAG_SCROLLABLE); 

    ui_Label1 = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    ui_pres = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_pres, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_pres, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_pres, LV_ALIGN_CENTER);

    ui_temp = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_temp, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_temp, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_temp, LV_ALIGN_CENTER);


    lv_label_set_text(ui_Label1,"BMP280 (TP)");
    lv_label_set_text(ui_pres,"0 hPa");
    lv_label_set_text(ui_temp,"Temp: 0 °C");
        // Call construct LVGL functions here
    }
};

/**************************************************************************/
/**
 * @class GAT
 * @brief Gyroscope/Accelerometr/Temperature sensor class derived from BaseSensor.
 * 
 * Represents a Gyroscope/Accelerometr/Temperature sensor. Implements initialization, configuration, updating, and printing
 * specific to Gyroscope/Accelerometr/Temperature sensors.
 */

 class GAT : public BaseSensor {
    public:
        /**
         * @brief Constructs a new GAT object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        GAT(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~GAT() {}

        lv_obj_t* ui_Label1;
        lv_obj_t* ui_Label2;
        lv_obj_t* ui_acm_x;
        lv_obj_t* ui_acm_y;
        lv_obj_t* ui_acm_z;
        lv_obj_t* ui_Label6;
        lv_obj_t* ui_gyr_x;
        lv_obj_t* ui_gyr_y;
        lv_obj_t* ui_gyr_z;
        lv_obj_t* ui_temp;
        lv_obj_t * ui_Panel3;

    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "GAT";
            Description = "Gyroscope/Accelerometr/Temperature sensor";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("Precision", {"2", "decimals", DataType::INT});
                // Default values
                addValueParameter("Temperature", {"0", "°C", DataType::FLOAT});
                addValueParameter("G", {"0", "g", DataType::FLOAT});
                addValueParameter("degrees per second", {"0", "°/s", DataType::FLOAT});

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

    lv_label_set_text(ui_acm_x,"x: 0 G");
    lv_label_set_text(ui_acm_y,"y: 0 G");
    lv_label_set_text(ui_acm_z,"z: 0 G");
    lv_label_set_text(ui_gyr_x,"x: 0 °/s");
    lv_label_set_text(ui_gyr_y,"y: 0 °/s");
    lv_label_set_text(ui_gyr_z,"z: 0 °/s");
    lv_label_set_text(ui_temp,"Temp: 0 °C");

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
        
        
    ui_Panel3= lv_obj_create(lv_scr_act());
    lv_obj_set_width(ui_Panel3, 140);
    lv_obj_set_height(ui_Panel3, 190);
    lv_obj_set_align(ui_Panel3, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel3, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Panel3, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_set_scroll_dir(ui_Panel3, LV_DIR_VER);
    lv_obj_add_flag(ui_Panel3, LV_OBJ_FLAG_SCROLLABLE);
    

    ui_Label1 = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    ui_Label2 = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);

    ui_acm_x = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_acm_x, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_acm_x, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_acm_x, LV_ALIGN_CENTER);

    ui_acm_y = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_acm_y, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_acm_y, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_acm_y, LV_ALIGN_CENTER);

    ui_acm_z = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_acm_z, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_acm_z, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_acm_z, LV_ALIGN_CENTER);

    ui_Label6 = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);

    ui_gyr_x = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_gyr_x, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_gyr_x, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_gyr_x, LV_ALIGN_CENTER);

    ui_gyr_y = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_gyr_y, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_gyr_y, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_gyr_y, LV_ALIGN_CENTER);

    ui_gyr_z = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_gyr_z, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_gyr_z, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_gyr_z, LV_ALIGN_CENTER);

    ui_temp = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_temp, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_temp, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_temp, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1,"GY-521 (GAT)");
    lv_label_set_text(ui_Label2,"Accelerometr");
    lv_label_set_text(ui_acm_x,"x: 0 G");
    lv_label_set_text(ui_acm_y,"y: 0 G");
    lv_label_set_text(ui_acm_z,"z: 0 G");
    lv_label_set_text(ui_Label6,"Gyroscope");
    lv_label_set_text(ui_gyr_x,"x: 0 °/s");
    lv_label_set_text(ui_gyr_y,"y: 0 °/s");
    lv_label_set_text(ui_gyr_z,"z: 0 °/s");
    lv_label_set_text(ui_temp,"Temp: 0 °C");



    
        // Call construct LVGL functions here
    }
};


/**************************************************************************/
/**
 * @class TOF
 * @brief Time of flight sensor class derived from BaseSensor.
 * 
 * Represents a Time of flight sensor. Implements initialization, configuration, updating, and printing
 * specific to Time of flight sensors.
 */

 class TOF : public BaseSensor {
    public:
        /**
         * @brief Constructs a new GAT object.
         * 
         * Initializes default values and sets the sensor type and description.
         * 
         * @param uid The unique sensor identifier.
         */
        TOF(std::string uid) : BaseSensor(uid)
        {
            init();
        }
    
        /**
         * @brief Virtual destructor.
         */
        virtual ~TOF() {}
        lv_obj_t* ui_Label1;
        lv_obj_t* ui_distance;
        lv_obj_t * ui_Panel3;
    
        /**
         * @brief Initializes the sensor.
         * 
         * Additional initialization code can be added here.
         * 
         * @throws Exception if initialization fails.
         */
        virtual void init() override {
            // Additional initialization for sensor can be added here.
            Type = "TOF";
            Description = "Time of flight sensor";
            Error = nullptr;
    
            try
            {
                // Default configs
                addConfigParameter("Precision", {"2", "decimals", DataType::INT});
                // Default values
                addValueParameter("Distance", {"0", "meters", DataType::FLOAT});
                
    


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
            lv_label_set_text(ui_distance,"110 mm");
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
        
        
    ui_Panel3= lv_obj_create(lv_scr_act());
    lv_obj_set_width(ui_Panel3, 140);
    lv_obj_set_height(ui_Panel3, 190);
    lv_obj_set_align(ui_Panel3, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Panel3, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(ui_Panel3, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_Panel3, LV_OBJ_FLAG_SCROLLABLE); 

    ui_Label1 = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);

    ui_distance = lv_label_create(ui_Panel3);
    lv_obj_set_width(ui_distance, LV_SIZE_CONTENT);   
    lv_obj_set_height(ui_distance, LV_SIZE_CONTENT);    
    lv_obj_set_align(ui_distance, LV_ALIGN_CENTER);

    lv_label_set_text(ui_Label1,"VL53L0X (TOF)");
    lv_label_set_text(ui_distance,"0 mm");
        // Call construct LVGL functions here
    }
};
#endif //SENSORS_HPP