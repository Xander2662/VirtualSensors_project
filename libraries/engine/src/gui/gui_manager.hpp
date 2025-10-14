/**
 * @file gui_manager.hpp
 * @brief Declaration of the GuiManager class
 *
 * This header defines the GuiManager class which coordinates
 * between MenuGui and SensorVisualizationGui components, providing
 * a central access point for GUI operations.
 *
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny, Ondřej Wrubel
 */

#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include "menu_gui.hpp"
#include "sensor_visualization_gui.hpp"
#include "../managers/manager.hpp"

/**
 * @brief Enumeration for different GUI states
 */
enum class GuiState {
    MENU,           ///< Main menu with pin assignment
    VISUALIZATION,  ///< Sensor data visualization
    WIKI           ///< Sensor documentation/wiki
};

/**
 * @brief GUI Manager class
 * 
 * This class serves as a central coordinator that initializes GUI components
 * and handles screen switching between menu and sensor visualization.
 */
class GuiManager {
private:
    SensorManager &sensorManager;           ///< Reference to sensor manager
    MenuGui menuGui;                        ///< Menu and pin assignment component
    SensorVisualizationGui vizGui;          ///< Sensor visualization component
    
    GuiState currentState;                  ///< Current GUI state
    bool initialized;                       ///< Initialization flag
    
    /**
     * @brief Hide all GUI components
     */
    void hideAllComponents();

public:
    /**
     * @brief Constructor
     * @param manager Reference to the SensorManager instance
     */
    explicit GuiManager(SensorManager &manager);
    
    /**
     * @brief Initialize the unified GUI manager and all components
     */
    void init();
    
    /**
     * @brief Check if the GUI manager is initialized
     * @return true if initialized, false otherwise
     */
    bool isInitialized() const { return initialized; }
    
    // === SCREEN SWITCHING ===
    
    /**
     * @brief Get current GUI state
     * @return Current GuiState
     */
    GuiState getCurrentState() const { return currentState; }
    
    /**
     * @brief Switch to menu screen
     */
    void showMenu();
    
    /**
     * @brief Switch to sensor visualization screen
     */
    void showVisualization();
    
    /**
     * @brief Switch to sensor wiki screen
     */
    void showWiki();
    
    // === COMPONENT ACCESS ===
    
    /**
     * @brief Get reference to menu GUI component
     * @return Reference to MenuGui
     */
    MenuGui& getMenuGui() { return menuGui; }
    
    /**
     * @brief Get reference to visualization GUI component
     * @return Reference to SensorVisualizationGui
     */
    SensorVisualizationGui& getVisualizationGui() { return vizGui; }
    
    /**
     * @brief Get reference to sensor manager
     * @return Reference to SensorManager
     */
    SensorManager& getSensorManager() { return sensorManager; }
};

#endif // GUI_MANAGER_HPP