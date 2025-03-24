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
#include "base_sensor.hpp" ///< BaseSensor class.

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
class ADC : public BaseSensor
{
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

    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "ADC";
        Description = "Analog to Digital Converter";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("resolution", {"12", "bits", DataType::INT, 0});
            // Default values
            addValueParameter("value", {"0", "", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        // TODO: Implement draw function

        redrawPenging = false; // Reset flag to redraw sensor.
    }

    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
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
class Joystick : public BaseSensor
{
protected:
    //Container
    lv_obj_t *ui_Widget;
    lv_obj_t *ui_Label;
    //Parametrs
    lv_obj_t *ui_Value_X;
    lv_obj_t *ui_Value_Y;
    lv_obj_t *ui_Value_SW;
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "Joystick";
        Description = "Joystick peripheral";
        Error = nullptr;

        try
        {
            // Default configs
                // If there are no configs, you can skip this step
            // Default values
            addValueParameter("XCoordination", {"50", "%", DataType::INT, 0});
            addValueParameter("YCoordination", {"50", "%", DataType::INT, 0});
            addValueParameter("Button", {"0", "ON/OFF", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string x = "X: " + getValue<std::string>("XCoordination");
        std::string y = "Y: " + getValue<std::string>("YCoordination");
        std::string sw = "SW: " + getValue<std::string>("Button");
        lv_label_set_text(ui_Value_X, x.c_str());
        lv_label_set_text(ui_Value_Y, y.c_str());
        lv_label_set_text(ui_Value_SW, sw.c_str());
        

        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Value_X = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_X, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_X, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_X, LV_ALIGN_CENTER);

        ui_Value_Y = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_Y, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_Y, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_Y, LV_ALIGN_CENTER);

        ui_Value_SW = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_SW, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_SW, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_SW, LV_ALIGN_CENTER);
    

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Value_X, "X: 0");
        lv_label_set_text(ui_Value_Y, "Y: 0");
        lv_label_set_text(ui_Value_SW, "SW: 0");
        // Call construct LVGL functions here
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
class DHT11 : public BaseSensor
{
protected:
    //Container
    lv_obj_t *ui_Widget;
    lv_obj_t *ui_Label;
    //Parametrs
    lv_obj_t *ui_Value_T;
    lv_obj_t *ui_Value_H;
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "DHT11";
        Description = "DHT11 Temperature & Humidity sensor";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("resolution", {"3", "digits", DataType::INT, 0});
            // Default values
            addValueParameter("Temperature", {"0", "°C", DataType::INT, 0});
            addValueParameter("Humidity", {"0", "%", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string t = "Temperature: " + getValue<std::string>("Temperature") + " °C";
        std::string h = "Humidity: " + getValue<std::string>("Humidity") + " %";
        lv_label_set_text(ui_Value_T, t.c_str());
        lv_label_set_text(ui_Value_H, h.c_str());

        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Value_T = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_T, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_T, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_T, LV_ALIGN_CENTER);

        ui_Value_H = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_H, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_H, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_H, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Value_T, "Temperature: 0 °C");
        lv_label_set_text(ui_Value_H, "Humidity: 0 %");

        // Call construct LVGL functions here
    }
};

/**************************************************************************/

/**
 * @class LinearHallAndDigital
 * @brief LinearHallAndDigital sensor class derived from BaseSensor.
 *
 * Represents a Linear Hall sensor, which returns strenght of a magnet in milliTesla. Implements initialization, configuration,
 * updating, and printing specific to LinearHallAndDigital sensors.
 */
class LinearHallAndDigital : public BaseSensor
{
    protected:
    //Container
    lv_obj_t *ui_Widget;
    lv_obj_t *ui_Label;
    //Parameters
    lv_obj_t *ui_Value_MT; // MilliTesla
    lv_obj_t *ui_Value_MD; // Magnet Detector
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "LinearHallAndDigital";
        Description = "Returns milliTesla of a measured magnet and if he goes past linearity";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("precision", {"2", "decimals", DataType::INT, 0});
            // Default values
            addValueParameter("milliTesla Meter", {"0", "mT", DataType::FLOAT, 0});
            addValueParameter("Magnet Detector", {"0", "", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string t = "milliTesla Meter: " + getValue<std::string>("milliTesla Meter") + " mT";
        std::string h = "Magnet Detector: " + getValue<std::string>("Magnet Detector");
        lv_label_set_text(ui_Value_MT, t.c_str());
        lv_label_set_text(ui_Value_MD, h.c_str());


        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Value_MT = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_MT, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_MT, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_MT, LV_ALIGN_CENTER);

        ui_Value_MD = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_MD, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_MD, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_MD, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Value_MT, "milliTesla Meter: 0 mT");
        lv_label_set_text(ui_Value_MD, "Magnet Detector: 0");
        // Call construct LVGL functions here
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
class PhotoResistor : public BaseSensor
{
protected:
lv_obj_t *ui_Widget;
lv_obj_t *ui_Label;
lv_obj_t *ui_Value_Lux;
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "PhotoResistor";
        Description = "Returns Lux of a measured environment, which users is in";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("resolution", {"5", "digits", DataType::INT, 0});
            // Default values
            addValueParameter("Lux Meter", {"0", "Lux", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string t = "Lux Meter: " + getValue<std::string>("Lux Meter") + " Lux";
        lv_label_set_text(ui_Value_Lux, t.c_str());


        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Value_Lux = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_Lux, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_Lux, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_Lux, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Value_Lux, "Lux Meter: 0 Lux");
        // Call construct LVGL functions here
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
class LinearHall : public BaseSensor
{
protected:
lv_obj_t *ui_Label;
lv_obj_t *ui_Value_MT;
lv_obj_t *ui_Widget;
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "LinearHall";
        Description = "Returns milliTesla of a measured magnet";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("precision", {"2", "decimals", DataType::INT, 0});
            // Default values
            addValueParameter("milliTesla Meter", {"0", "milliTesla", DataType::FLOAT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string t = "milliTesla Meter: " + getValue<std::string>("milliTesla Meter") + " mT";
        lv_label_set_text(ui_Value_MT, t.c_str());

        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Value_MT = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_MT, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_MT, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_MT, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Value_MT, "milliTesla Meter: 0 mT");
        // Call construct LVGL functions here
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
class DigitalTemperature : public BaseSensor
{
protected:
lv_obj_t *ui_Widget;
lv_obj_t *ui_Label;
lv_obj_t *ui_Value_TD; //Temperature Digital
lv_obj_t *ui_Value_TA; //Temperature Analog
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "DigitalTemperature";
        Description = "Returns temperature in °C and if the temperature goes past a hardware-configured value";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("precision", {"2", "decimals", DataType::INT, 0});
            // Default values
            addValueParameter("Temperature", {"0", "°C", DataType::FLOAT, 0});
            addValueParameter("Threshold", {"0", "", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string ta = "Temperature: " + getValue<std::string>("Temperature") + " °C";
        std::string td = "Threshold: " + getValue<std::string>("Threshold");
        lv_label_set_text(ui_Value_TA, ta.c_str());
        lv_label_set_text(ui_Value_TD, td.c_str());

        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Value_TA = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_TA, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_TA, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_TA, LV_ALIGN_CENTER);

        ui_Value_TD = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_TD, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_TD, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_TD, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Value_TA, "Temperature: 0 °C");
        lv_label_set_text(ui_Value_TD, "Threshold: 0");
        // Call construct LVGL functions here
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
class AnalogTemperature : public BaseSensor
{
protected:
lv_obj_t *ui_Widget;
lv_obj_t *ui_Label;
lv_obj_t *ui_Value_T;
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "AnalogTemperature";
        Description = "Returns temperature in °C";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("precision", {"2", "decimals", DataType::INT, 0});
            // Default values
            addValueParameter("Temperature", {"0", "°C", DataType::FLOAT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string t = "Temperature: " + getValue<std::string>("Temperature") + " °C";
        lv_label_set_text(ui_Value_T, t.c_str());

        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Value_T = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_T, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_T, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_T, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Value_T, "Temperature: 0 °C");
        // Call construct LVGL functions here
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
class TH : public BaseSensor
{
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "TH";
        Description = "Temperature & Humidity Sensor";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("precision", {"2", "decimals", DataType::INT, 0});
            // Default values
            addValueParameter("temperature", {"0", "Celsia", DataType::FLOAT, 0});
            addValueParameter("humidity", {"0", "%", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }
        // Draw sensor
        // Call draw function here
        // TODO: Implement draw function

        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
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
class DigitalHall : public BaseSensor
{
protected:
lv_obj_t *ui_Widget;
lv_obj_t *ui_Label;
lv_obj_t *ui_Value_D; //Digital
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "DigitalHall";
        Description = "Returns 1 of a measured magnet and if he goes past linearity";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("resolution", {"1", "bits", DataType::INT, 0});
            // Default values
            addValueParameter("Magnet Detector", {"0", "", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string d = "Magnet Detector: " + getValue<std::string>("Magnet Detector");
        lv_label_set_text(ui_Value_D, d.c_str());

        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Value_D = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_D, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_D, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_D, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Value_D, "Magnet Detector: 0");
        // Call construct LVGL functions here
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
class PhotoInterrupter : public BaseSensor
{
    protected:
    lv_obj_t *ui_Widget;
    lv_obj_t *ui_Label;
    lv_obj_t *ui_Value_D; //Digital
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
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "PhotoInterrupter";
        Description = "Returns 1 of a measured magnet and if he goes past linearity";
        Error = nullptr;

        try
        {
            // Default values
            addValueParameter("Motion Detector", {"0", "", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }

        // Draw sensor

        // Call draw function here
        std::string d = "Motion Detector: " + getValue<std::string>("Motion Detector");
        lv_label_set_text(ui_Value_D, d.c_str());

        redrawPenging = false; // Reset flag to redraw sensor.
    }
    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Value_D = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Value_D, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Value_D, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Value_D, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Value_D, "Motion Detector: 0");
        // Call construct LVGL functions here
    }
    // put me here12
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

class TP : public BaseSensor
{
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
    lv_obj_t *ui_Label;
    lv_obj_t *ui_temp;
    lv_obj_t *ui_pres;

    lv_obj_t *ui_Chart;
    lv_chart_series_t * ui_Chart_series_1;
    lv_chart_series_t * ui_Chart_series_2;

    lv_obj_t *ui_Widget;

    /**
     * @brief Initializes the sensor.
     *
     * Additional initialization code can be added here.
     *
     * @throws Exception if initialization fails.
     */
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "TP";
        Description = "Temperature & Pressure Sensor";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("Precision", {"2", "decimals", DataType::INT, 0});
            // Default values
            addValueParameter("Temperature", {"0", "°C", DataType::FLOAT, 0});
            addValueParameter("Pressure", {"0", "hPa", DataType::FLOAT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }
        // Draw sensor
        std::string temp = "temp: " + getValue<std::string>("Temperature")+" °C";
        std::string pres = "pres: " + getValue<std::string>("Pressure")+" hPa";
        lv_label_set_text(ui_pres, pres.c_str());
        lv_label_set_text(ui_temp, temp.c_str());
        // Call draw function here
        // TODO: Implement draw function¨

        //Example of update chart
        static lv_coord_t ui_Chart_series_temp[HISTORY_CAP];
        getHistory<float>("Temperature", ui_Chart_series_temp);
        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_2, ui_Chart_series_temp);

        static lv_coord_t ui_Chart_series_press[HISTORY_CAP];
        getHistory<float>("Pressure", ui_Chart_series_press);
        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_1, ui_Chart_series_press);
        
        redrawPenging = false; // Reset flag to redraw sensor.
    }

    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_pres = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_pres, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_pres, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_pres, LV_ALIGN_CENTER);

        ui_temp = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_temp, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_temp, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_temp, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_pres, "0 hPa");
        lv_label_set_text(ui_temp, "Temp: 0 °C");
        // Call construct LVGL functions here

        //Example of add chart
        ui_Chart = lv_chart_create(ui_Widget);
        lv_obj_set_width(ui_Chart, 75);
        lv_obj_set_height(ui_Chart, 50);
        lv_obj_set_x(ui_Chart, 10);
        lv_obj_set_y(ui_Chart, 100);
        lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
        lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
        lv_chart_set_range(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 500, 1200);
        lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
        lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
        lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);

        ui_Chart_series_1 = lv_chart_add_series(ui_Chart, lv_color_hex(0xFF7F00), LV_CHART_AXIS_PRIMARY_Y);
        lv_coord_t ui_Chart_series_temp[HISTORY_CAP];
        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_1, ui_Chart_series_temp);

        ui_Chart_series_2 = lv_chart_add_series(ui_Chart, lv_color_hex(0x7205FF),
                                                                    LV_CHART_AXIS_SECONDARY_Y);
        lv_coord_t ui_Chart_series_press[HISTORY_CAP];
        lv_chart_set_ext_y_array(ui_Chart, ui_Chart_series_2, ui_Chart_series_press);
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

class GAT : public BaseSensor
{
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

    lv_obj_t *ui_Label;
    lv_obj_t *ui_Label2;
    lv_obj_t *ui_acm_x;
    lv_obj_t *ui_acm_y;
    lv_obj_t *ui_acm_z;
    lv_obj_t *ui_Label6;
    lv_obj_t *ui_gyr_x;
    lv_obj_t *ui_gyr_y;
    lv_obj_t *ui_gyr_z;
    lv_obj_t *ui_temp;
    lv_obj_t *ui_Widget;

    /**
     * @brief Initializes the sensor.
     *
     * Additional initialization code can be added here.
     *
     * @throws Exception if initialization fails.
     */
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "GAT";
        Description = "Gyroscope/Accelerometr/Temperature sensor";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("Precision", {"2", "decimals", DataType::INT, 0});
            // Default values
            addValueParameter("Temperature", {"0", "°C", DataType::FLOAT, 0});
            addValueParameter("acm_x",{"0", "g", DataType::FLOAT, 0});
            addValueParameter("acm_y",{"0", "g", DataType::FLOAT, 0});
            addValueParameter("acm_z",{"0", "g", DataType::FLOAT, 0});
            addValueParameter("gyr_x",{"0", "°/s", DataType::FLOAT, 0});
            addValueParameter("gyr_y",{"0", "°/s", DataType::FLOAT, 0});
            addValueParameter("gyr_z",{"0", "°/s", DataType::FLOAT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }
        // Draw sensor
        std::string acm_x = "acm_x: " + getValue<std::string>("acm_x")+" g";
        std::string acm_y = "acm_y: " + getValue<std::string>("acm_y")+" g";
        std::string acm_z = "acm_z: " + getValue<std::string>("acm_z")+" g";
        std::string gyr_x = "gyr_x: " + getValue<std::string>("gyr_x")+" °/s";
        std::string gyr_y = "gyr_y: " + getValue<std::string>("gyr_y")+" °/s";
        std::string gyr_z = "gyr_z: " + getValue<std::string>("gyr_z")+" °/s";
        std::string temp = "Temp: " + getValue<std::string>("Temperature")+" °C";
        
        lv_label_set_text(ui_acm_x, acm_x.c_str());
        lv_label_set_text(ui_acm_y, acm_y.c_str());
        lv_label_set_text(ui_acm_z, acm_z.c_str());
        lv_label_set_text(ui_gyr_x, gyr_x.c_str());
        lv_label_set_text(ui_gyr_y, gyr_y.c_str());
        lv_label_set_text(ui_gyr_z, gyr_z.c_str());
        lv_label_set_text(ui_temp,  temp.c_str());

        // Call draw function here
        // TODO: Implement draw function

        redrawPenging = false; // Reset flag to redraw sensor.
    }

    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_scroll_dir(ui_Widget, LV_DIR_VER);
        lv_obj_add_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_Label2 = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);

        ui_acm_x = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_acm_x, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_acm_x, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_acm_x, LV_ALIGN_CENTER);

        ui_acm_y = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_acm_y, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_acm_y, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_acm_y, LV_ALIGN_CENTER);

        ui_acm_z = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_acm_z, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_acm_z, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_acm_z, LV_ALIGN_CENTER);

        ui_Label6 = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);

        ui_gyr_x = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_gyr_x, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_gyr_x, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_gyr_x, LV_ALIGN_CENTER);

        ui_gyr_y = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_gyr_y, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_gyr_y, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_gyr_y, LV_ALIGN_CENTER);

        ui_gyr_z = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_gyr_z, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_gyr_z, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_gyr_z, LV_ALIGN_CENTER);

        ui_temp = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_temp, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_temp, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_temp, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_Label2, "Accelerometr");
        lv_label_set_text(ui_acm_x, "x: 0 G");
        lv_label_set_text(ui_acm_y, "y: 0 G");
        lv_label_set_text(ui_acm_z, "z: 0 G");
        lv_label_set_text(ui_Label6, "Gyroscope");
        lv_label_set_text(ui_gyr_x, "x: 0 °/s");
        lv_label_set_text(ui_gyr_y, "y: 0 °/s");
        lv_label_set_text(ui_gyr_z, "z: 0 °/s");
        lv_label_set_text(ui_temp, "Temp: 0 °C");

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

class TOF : public BaseSensor
{
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
    lv_obj_t *ui_Label;
    lv_obj_t *ui_distance;
    lv_obj_t *ui_Widget;

    /**
     * @brief Initializes the sensor.
     *
     * Additional initialization code can be added here.
     *
     * @throws Exception if initialization fails.
     */
    virtual void init() override
    {
        // Additional initialization for sensor can be added here.
        Type = "TOF";
        Description = "Time of flight sensor";
        Error = nullptr;

        try
        {
            // Default configs
            addConfigParameter("Precision", {"2", "decimals", DataType::INT, 0});
            // Default values
            addValueParameter("Distance", {"0", "milimeters", DataType::INT, 0});
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    /**
     * @brief Draw sensor.
     *
     * This function draws the sensor.
     */
    virtual void draw() override
    {
        if (!redrawPenging)
        {
            return;
        }
        // Draw sensor
        std::string dist = "dist: " + getValue<std::string>("Distance")+"mm";
        lv_label_set_text(ui_distance, dist.c_str());
        // Call draw function here
        // TODO: Implement draw function

        redrawPenging = false; // Reset flag to redraw sensor.
    }

    /**
     * @brief Construct UI elements.
     *
     * This function constructs the sensor-specific GUI.
     */
    virtual void construct() override
    {
        // Construct sensor UI

        ui_Widget = lv_obj_create(lv_scr_act());
        lv_obj_set_width(ui_Widget, 180);
        lv_obj_set_height(ui_Widget, 210);
        lv_obj_set_align(ui_Widget, LV_ALIGN_CENTER);
        lv_obj_set_flex_flow(ui_Widget, LV_FLEX_FLOW_COLUMN_WRAP);
        lv_obj_set_flex_align(ui_Widget, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_clear_flag(ui_Widget, LV_OBJ_FLAG_SCROLLABLE);

        ui_Label = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_Label, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_Label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_Label, LV_ALIGN_CENTER);

        ui_distance = lv_label_create(ui_Widget);
        lv_obj_set_width(ui_distance, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_distance, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_distance, LV_ALIGN_CENTER);

        lv_label_set_text(ui_Label, Type.c_str());
        lv_label_set_text(ui_distance, "dist: 0 mm");
        // Call construct LVGL functions here
    }
};
#endif // SENSORS_HPP