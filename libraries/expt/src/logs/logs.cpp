/**
 * @file logs.c
 * @brief Implementation of logging functions.
 * 
 * @copyright 2024 MTA
 * @author 
 * Ing. Jiri Konecny
 */

#include "logs.hpp"

std::string buildMessage(const char *format, ...) {
    char buffer[512];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    return std::string(buffer);
}

#ifdef ARDUINO_H
    #include <Arduino.h>  ///< Include Arduino Serial functions
#elif defined(STDIO_H)
    #include <stdio.h>    ///< Include standard I/O functions
#endif

void logMessage(const char *format, ...) {
    va_list args;
    va_start(args, format);

    #ifdef ARDUINO_H
        if(!Serial)
        {
            initLogger();
        }
        // Create a buffer for formatted output
        char buffer[256];
        vsnprintf(buffer, sizeof(buffer), format, args);
        Serial.println(buffer);  // Print via Arduino Serial
    #elif defined(STDIO_H)
        vprintf(format, args);  // Print via standard console
    #endif
    va_end(args);
}

void initLogger() {
    #ifdef ARDUINO_H
        Serial.begin(UART0_BAUDRATE); // Initialize Serial for Arduino
        Serial.setTimeout(UART0_TIMEOUT);
    #endif
}

