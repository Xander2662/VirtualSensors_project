/**
 * @file main_menu.hpp
 * @brief Declaration of the manager_GUI widget
 *
 * This header defines the manager_GUI class which provides
 * a widget with a Start button and 6 pin selection buttons.
 *
 * @copyright 2025 MTA
 * @author Ondřej Wrubel
 */

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "lvgl.h"
#include <array>

#include "../managers/manager.hpp"
#include "../sensors/base_sensor.hpp"

class manager_GUI
{
private:
    /**
     * @brief Private constructor for singleton pattern
     */
    manager_GUI();
    ~manager_GUI() = default;

    manager_GUI(const manager_GUI &) = delete;
    manager_GUI &operator=(const manager_GUI &) = delete;

    bool initialized = false;  ///< Initialization state flag

    // --- MENU GUI MEMBERS ---

    lv_obj_t *ui_MenuWidget;                ///< Main menu widget
    lv_obj_t *ui_ButtonStartGroup;          ///< Group for start button
    lv_obj_t *ui_ButtonStartCornerTopLeft;  ///< Top-left corner decoration
    lv_obj_t *ui_ButtonStartCornerBottomRight; ///< Bottom-right corner decoration
    lv_obj_t *ui_btnStart;                  ///< Start button
    lv_obj_t *ui_ButtonStartLabel;          ///< Label for start button
    std::array<lv_obj_t *, NUM_PINS> pinContainers;///< Containers for pin selection
    std::array<lv_obj_t *, NUM_PINS> pinLabels;    ///< Labels for pin selection

    /**
     * @brief Build the menu GUI widgets
     */
    void buildMenu();

    // --- SENSOR GUI MEMBERS ---

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

    // --- WIKI MEMBERS ---

    lv_obj_t *ui_SensorWidgetWiki;          ///< Widget for sensor wiki
    lv_obj_t *ui_SensorLabelWiki;           ///< Wiki label for sensor name
    lv_obj_t *ui_SensorLabelDescription;    ///< Wiki label for sensor description
    lv_obj_t *ui_SensorImage;               ///< Image for sensor wiki

    // --- SENSOR EVENT GUI MEMBERS ---

    lv_obj_t *ui_btnPrev;                   ///< Previous sensor button
    lv_obj_t *ui_btnPrevLabel;              ///< Label for previous button
    lv_obj_t *ui_btnNext;                   ///< Next sensor button
    lv_obj_t *ui_btnNextLabel;              ///< Label for next button
    lv_obj_t *ui_btnConfirm;                ///< Confirm button
    lv_obj_t *ui_btnConfirmLabel;           ///< Label for confirm button

    /**
     * @brief Add navigation buttons to a widget
     * @param parentWidget The parent widget to add buttons to
     * @param isVisualisation If true, for visualisation, else for wiki
     */
    void addNavButtonsToWidget(lv_obj_t *parentWidget, bool isVisualisation = true);

    /**
     * @brief Add a confirm button to a widget
     * @param parentWidget The parent widget to add the button to
     */
    void addConfirmButtonToWidget(lv_obj_t *parentWidget);

    /**
     * @brief Add a back button to a widget
     * @param parentWidget The parent widget to add the button to
     */
    void addBackButtonToWidget(lv_obj_t *parentWidget);

public:
    /**
     * @brief Get the singleton instance of manager_GUI
     */
    static manager_GUI &getInstance();

    /**
     * @brief Initialize the GUI manager and sensors
     */
    void init();

    /**
     * @brief Check if the manager has been initialized
     * @return True if initialized, false otherwise
     */
    bool isInitialized() const { return initialized; }

    /**
     * @brief Show the main menu GUI
     */
    void showMenu();

    /**
     * @brief Hide the main menu GUI
     */
    void hideMenu();

    /**
     * @brief Update the text labels for pin selections
     */
    void updatePinLabelText();

    /**
     * @brief Draw the currently selected sensor's GUI
     */
    void drawCurrentSensor();

    /**
     * @brief Construct the main menu and sensor widgets
     */
    void construct();

    /**
     * @brief Construct the sensor wiki widget
     */
    void constructWiki();

    /**
     * @brief Go to the first sensor in the list
     * @param isVisualisation If true, show visualisation, otherwise show wiki
     */
    void goToFirstSensor(bool isVisualisation);

    /**
     * @brief Show the sensor wiki screen
     */
    void showSensorWiki();

    /**
     * @brief Hide the sensor wiki screen
     */
    void hideSensorWiki();

    /**
     * @brief Show the sensor visualisation screen
     */
    void showSensorVisualisation();

    /**
     * @brief Hide the sensor visualisation screen
     */
    void hideSensorVisualisation();
};

#endif
