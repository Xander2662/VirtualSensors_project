/**
 * @file menu_gui.hpp
 * @brief Declaration of the MenuGui widget
 *
 * This header defines the MenuGui class which provides
 * a widget with a Start button and pin selection/assignment functionality.
 * Focused on menu visualization and sensor-to-pin assignment operations.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */

#ifndef MENU_GUI_HPP
#define MENU_GUI_HPP

#include "lvgl.h"
#include <array>

#include "../managers/manager.hpp"
#include "../sensors/base_sensor.hpp"

/**
 * @class MenuGui
 * @brief Handles menu visualization and sensor-to-pin assignment functionality.
 *
 * This class is responsible for:
 * - Displaying the main menu with start button and pin selection
 * - Managing pin assignment interface and active pin selection
 * - Handling menu-related events and navigation
 * - Providing interface for sensor-to-pin mapping operations
 */
class MenuGui
{
private:
    SensorManager &sensorManager;  ///< Reference to the SensorManager instance
    bool initialized = false;      ///< Initialization state flag
    int activePinIndex = -1;       ///< Currently selected/active pin index (-1 = none)

    // --- MENU GUI MEMBERS ---
    lv_obj_t *ui_MenuWidget;                ///< Main menu widget
    lv_obj_t *ui_ButtonStartGroup;          ///< Group for start button
    lv_obj_t *ui_ButtonStartCornerTopLeft;  ///< Top-left corner decoration
    lv_obj_t *ui_ButtonStartCornerBottomRight; ///< Bottom-right corner decoration
    lv_obj_t *ui_btnStart;                  ///< Start button
    lv_obj_t *ui_ButtonStartLabel;          ///< Label for start button
    std::array<lv_obj_t *, NUM_PINS> pinContainers; ///< Containers for pin selection
    std::array<lv_obj_t *, NUM_PINS> pinLabels;     ///< Labels for pin selection

    /**
     * @brief Build the menu GUI widgets
     */
    void buildMenu();

    /**
     * @brief Update visual state of pin buttons based on assignments and selection
     */
    void updatePinVisualStates();
    
    /**
     * @brief Handle start button click event
     */
    void handleStartButtonClick();
    
    /**
     * @brief Handle pin button click event
     * @param pinIndex Index of the clicked pin
     */
    void handlePinClick(int pinIndex);
    
    /**
     * @brief Get pin index from container object
     * @param container The pin container object
     * @return Pin index or -1 if not found
     */
    int getIndexFromContainer(lv_obj_t* container);

public:
    /**
     * @brief Constructor
     * @param manager Reference to the SensorManager instance
     */
    MenuGui(SensorManager &manager);
    
    /**
     * @brief Destructor
     */
    ~MenuGui() = default;

    /**
     * @brief Initialize the menu GUI
     */
    void init();

    /**
     * @brief Check if the menu GUI has been initialized
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
     * @brief Update the text labels for pin selections based on assigned sensors
     */
    void updatePinLabels();

    /**
     * @brief Set the currently active/selected pin
     * @param pinIndex Index of the pin to set as active (-1 for none)
     */
    void setActivePin(int pinIndex);

    /**
     * @brief Get the currently active/selected pin index
     * @return Index of the active pin (-1 if none selected)
     */
    int getActivePin() const { return activePinIndex; }

    /**
     * @brief Assign the current sensor to the active pin
     * @return True if assignment was successful, false otherwise
     */
    bool assignCurrentSensorToActivePin();

    /**
     * @brief Unassign sensor from the active pin
     * @return True if unassignment was successful, false otherwise
     */
    bool unassignSensorFromActivePin();

    /**
     * @brief Check if a pin has a sensor assigned
     * @param pinIndex Index of the pin to check
     * @return True if pin has an assigned sensor, false otherwise
     */
    bool isPinAssigned(int pinIndex) const;

    /**
     * @brief Get the sensor assigned to a specific pin
     * @param pinIndex Index of the pin
     * @return Pointer to assigned sensor or nullptr if none
     */
    BaseSensor* getAssignedSensor(int pinIndex) const;

    /**
     * @brief Get reference to the sensor manager
     * @return Reference to SensorManager instance
     */
    SensorManager& getSensorManager() { return sensorManager; }
};

#endif // MENU_GUI_HPP