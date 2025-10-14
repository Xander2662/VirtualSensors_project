/**
 * @file sensor_visualization_gui.hpp
 * @brief Declaration of the SensorVisualizationGui widget
 *
 * This header defines the SensorVisualizationGui class which handles
 * active sensor visualization, data display, synchronization, and navigation.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */

#ifndef SENSOR_VISUALIZATION_GUI_HPP
#define SENSOR_VISUALIZATION_GUI_HPP

#include "lvgl.h"
#include <array>
#include <map>

#include "../managers/manager.hpp"
#include "../sensors/base_sensor.hpp"
#include "../helpers.hpp"
#include "../exceptions/data_exceptions.hpp"

/**
 * @class SensorVisualizationGui
 * @brief Handles active sensor visualization, data display, and navigation.
 *
 * This class is responsible for:
 * - Displaying current sensor data and values
 * - Handling sensor navigation (prev/next)
 * - Managing sensor synchronization operations
 * - Providing sensor wiki/information display
 * - Handling sensor-specific events and interactions
 */
class SensorVisualizationGui
{
private:
    SensorManager &sensorManager;  ///< Reference to the SensorManager instance
    bool initialized = false;      ///< Initialization state flag

    // --- SENSOR VISUALIZATION MEMBERS ---
    lv_obj_t *ui_SensorWidget;              ///< Widget for sensor visualisation
    lv_obj_t *ui_SensorLabel;               ///< Label for sensor name
    
    // VALUE_1
    lv_obj_t *ui_ContainerForValue_1;       ///< Container for first value
    lv_obj_t *ui_VisualColorForValue_1;     ///< Color indicator for first value
    lv_obj_t *ui_LabelValueValue_1;         ///< Value label for first value
    lv_obj_t *ui_LabelDescValue_1;          ///< Description label for first value
    lv_obj_t *ui_LabelTypeValue_1;          ///< Type label for first value
    
    // VALUE_2
    lv_obj_t *ui_VisualColorForValue_2;     ///< Color indicator for second value
    lv_obj_t *ui_ContainerForValue_2;       ///< Container for second value
    lv_obj_t *ui_LabelValueValue_2;         ///< Value label for second value
    lv_obj_t *ui_LabelDescValue_2;          ///< Description label for second value
    lv_obj_t *ui_LabelTypeValue_2;          ///< Type label for second value
    
    // CHART
    lv_obj_t *ui_Chart;                     ///< Chart widget for sensor data
    lv_chart_series_t *ui_Chart_series_V1;  ///< Chart series for value 1
    lv_chart_series_t *ui_Chart_series_V2;  ///< Chart series for value 2

    // --- WIKI MEMBERS ---
    lv_obj_t *ui_SensorWidgetWiki;          ///< Widget for sensor wiki
    lv_obj_t *ui_SensorLabelWiki;           ///< Wiki label for sensor name
    lv_obj_t *ui_SensorLabelDescription;    ///< Wiki label for sensor description
    lv_obj_t *ui_SensorImage;               ///< Image for sensor wiki

    // --- NAVIGATION AND CONTROL MEMBERS ---
    lv_obj_t *ui_btnPrev;                   ///< Previous sensor button
    lv_obj_t *ui_btnPrevLabel;              ///< Label for previous button
    lv_obj_t *ui_btnNext;                   ///< Next sensor button
    lv_obj_t *ui_btnNextLabel;              ///< Label for next button
    lv_obj_t *ui_btnConfirm;                ///< Confirm button
    lv_obj_t *ui_btnConfirmLabel;           ///< Label for confirm button
    lv_obj_t *ui_btnSync;                   ///< Sync sensor button
    lv_obj_t *ui_btnSyncLabel;              ///< Label for sync button
    lv_obj_t *ui_btnBack;                   ///< Back to menu button
    lv_obj_t *ui_btnBackLabel;              ///< Label for back button

    /**
     * @brief Add navigation buttons to a widget
     * @param parentWidget The parent widget to add buttons to
     * @param isVisualisation If true, for visualisation, else for wiki
     */
    void addNavButtonsToWidget(lv_obj_t *parentWidget, bool isVisualisation = true);

    /**
     * @brief Add control buttons (sync, back) to a widget
     * @param parentWidget The parent widget to add the buttons to
     */
    void addControlButtonsToWidget(lv_obj_t *parentWidget);

    /**
     * @brief Build sensor history data for chart display
     * @param sensor Pointer to the sensor
     * @param key The key of the sensor parameter
     * @param history The history array to store the history
     */
    template <typename T>
    void buildSensorHistory(BaseSensor *sensor, const std::string &key, lv_coord_t *history) {
        if (!history || !sensor) return;

        auto it = sensor->getValues().find(key);
        if (it == sensor->getValues().end()) return;

        // Static storage between calls
        static std::map<std::string, std::array<lv_coord_t, HISTORY_CAP>> bufMap;
        static std::map<std::string, bool> initedMap;
    
        auto &buf    = bufMap[key];
        bool &inited = initedMap[key];
    
        // Get current value as string and convert
        lv_coord_t curr;
        try {
            std::string s = sensor->getValue<std::string>(key);
            curr = convertStringToType<T>(s);
        }
        catch (const std::exception &e) {
            throw InvalidDataTypeException("SensorVisualizationGui::buildSensorHistory", e.what());
        }
    
        if (!inited) {
            // First call: fill entire buffer with current value
            for (int i = 0; i < HISTORY_CAP; ++i) {
                buf[i] = curr;
            }
            inited = true;
        }
        else {
            // Shift left by one position
            for (int i = 0; i < HISTORY_CAP - 1; ++i) {
                buf[i] = buf[i + 1];
            }
            // Add current value at the end
            buf[HISTORY_CAP - 1] = curr;
        }
    
        // Copy entire buffer to output array
        for (int i = 0; i < HISTORY_CAP; ++i) {
            try {
                history[i] = buf[i];
            }
            catch (const std::exception &e) {
                throw InvalidDataTypeException("SensorVisualizationGui::buildSensorHistory", e.what());
            }
        }
    }

    /**
     * @brief Update sensor data display
     */
    void updateSensorDataDisplay();

    /**
     * @brief Update chart with current sensor data
     */
    void updateChart();

public:
    /**
     * @brief Constructor
     * @param manager Reference to the SensorManager instance
     */
    SensorVisualizationGui(SensorManager &manager);
    
    /**
     * @brief Destructor
     */
    ~SensorVisualizationGui() = default;

    /**
     * @brief Initialize the sensor visualization GUI
     */
    void init();

    /**
     * @brief Check if the visualization GUI has been initialized
     * @return True if initialized, false otherwise
     */
    bool isInitialized() const { return initialized; }

    /**
     * @brief Construct the sensor visualization widget
     */
    void constructVisualization();

    /**
     * @brief Construct the sensor wiki widget
     */
    void constructWiki();

    /**
     * @brief Draw/update the currently selected sensor's visualization
     */
    void drawCurrentSensor();

    /**
     * @brief Go to the previous sensor in the list
     */
    void goToPreviousSensor();

    /**
     * @brief Go to the next sensor in the list
     */
    void goToNextSensor();

    /**
     * @brief Go to the first sensor in the list
     * @param showWikiTrigger If true, show wiki, otherwise show visualization
     */
    void goToFirstSensor(bool showWikiTrigger = false);

    /**
     * @brief Synchronize the current sensor data
     * @return True if synchronization was successful, false otherwise
     */
    bool syncCurrentSensor();

    /**
     * @brief Show the sensor visualization screen
     */
    void showVisualization();

    /**
     * @brief Hide the sensor visualization screen
     */
    void hideVisualization();

    /**
     * @brief Show the sensor wiki screen
     */
    void showWiki();

    /**
     * @brief Hide the sensor wiki screen
     */
    void hideWiki();

    /**
     * @brief Get reference to the sensor manager
     * @return Reference to SensorManager instance
     */
    SensorManager& getSensorManager() { return sensorManager; }

    /**
     * @brief Get the current sensor being displayed
     * @return Pointer to current sensor or nullptr if none
     */
    BaseSensor* getCurrentSensor();
};

#endif // SENSOR_VISUALIZATION_GUI_HPP