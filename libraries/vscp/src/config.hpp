/**
 * @file config.h
 * @brief Configuration file for platform-specific settings.
 * 
 * This file defines macros to select the execution environment (Arduino or standard console).
 * Uncomment the desired macro to enable the respective environment.
 * 
 * @copyright 2025 MTA
 * @author Ing. Jiri Konecny
 */

#ifndef CONFIG_H
#define CONFIG_H

/// Uncomment to enable Arduino-based environments
#define ARDUINO_H 
#define UART1_PORT 0
#define UART1_BAUDRATE 115200
#define UART1_RX -1
#define UART1_TX -1
#define UART_TIMEOUT 100

/// Uncomment to enable standard console applications (PC/Linux)
//#define STDIO_H 

// Uncomment to enable LVGL support
//#define USE_LVGL

///Set whatever the application should be a case sensitive
#define CASE_SENSITIVE true

#endif // CONFIG_H