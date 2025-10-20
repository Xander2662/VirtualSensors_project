/**
 * @file messenger.cpp
 * @brief Definition of the messenger interface and related global functions.
 * 
 * This header defines the global functions for message operations. It includes configuration
 * and exception handling support..
 * 
 * @copyright 2024 MTA
 * @author 
 * Ing. Jiri Konecny
 */
#include "messenger.hpp"

#ifdef ARDUINO_H
    #include <Arduino.h>  ///< Include Arduino 
    #include <HardwareSerial.h> ///< Include Arduino Serial functions

    HardwareSerial UART1(UART1_PORT);

    void sendMessage(const std::string &message) {
        if(!UART1){
            initMessenger();
        }
        
        UART1.println(message.c_str());
    }
    
    std::string receiveMessage(int verbose, int timeout) {
        String msg = ""; // static so it persists between calls
        unsigned long startTime = millis();

        if(!UART1){
            initMessenger();
        }

        while (UART1.available() == 0 && (millis() - startTime) < UART_TIMEOUT) {
        // Wait until data arrives or timeout occurs
        }

        if (UART1.available() > 0) {
            // Read response
            msg = UART1.readString();
        } else {
            // Handle timeout situation
            if(verbose > 0)
            {
                msg = "Timeout occurred while waiting for message.";
            }
            else
            {
                msg = "";
            }
        }

        return std::string(msg.c_str());
    }

    bool initMessenger(unsigned long baudrate = UART1_BAUDRATE, unsigned int mode = SERIAL_8N1, int tx = UART1_TX, int rx = UART1_RX) {
        UART1.begin(baudrate, mode, tx, rx);
        unsigned long startTime = millis();

        while ((millis() - startTime) < UART_INIT_TIMEOUT && !UART1) {
            // Wait for Serial to initialize or timeout
        }
        if (!UART1) {
            return false; // Initialization failed
        }
        return true;
    }

    bool initMessenger() {
        return initMessenger(UART1_BAUDRATE, SERIAL_8N1, UART1_TX, UART1_RX);
    }

#elif defined(STDIO_H)
    #include <stdio.h>    ///< Include standard I/O functions

    void sendMessage(const std::string &message) {
        printf("%s\n", message.c_str());
    }

    std::string receiveMessage(int timeout, int verbose) {
        char buffer[256];
        scanf("%s", buffer);
        return std::string(buffer);
    }

    bool initMessenger() {
        // No initialization needed for standard I/O
        return true;
    }

#else
    #error "No valid platform defined. Please define ARDUINO_H or STDIO_H in config.hpp"
    
#endif