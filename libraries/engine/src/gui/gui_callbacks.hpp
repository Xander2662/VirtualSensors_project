/**
 * @file gui_callbacks.hpp
 * @brief Declaration of global GUI callback functions
 *
 * This header defines global callback functions that GUI components
 * can use to request screen switching operations. These functions
 * are implemented in the main ui.ino file and provide communication
 * between GUI components and the main GuiManager.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */

#ifndef GUI_CALLBACKS_HPP
#define GUI_CALLBACKS_HPP

/**
 * @brief Switch to menu screen and stop sensors
 * 
 * This function switches the GUI to menu mode and stops all sensor operations.
 * Typically called by the Back button in visualization screens.
 */
extern void switchToMenu();

/**
 * @brief Switch to sensor visualization screen
 * 
 * This function switches the GUI to sensor visualization mode.
 * Typically called after starting sensor operations.
 */
extern void switchToVisualization();

/**
 * @brief Switch to sensor wiki screen
 * 
 * This function switches the GUI to sensor wiki/documentation mode.
 */
extern void switchToWiki();

#endif // GUI_CALLBACKS_HPP