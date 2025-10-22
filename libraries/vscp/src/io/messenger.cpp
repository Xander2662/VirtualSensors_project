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

    HardwareSerial UART1_VIRTUAL(UART1_PORT);
    static bool uart1_initialized = false;

    void sendMessage(const std::string &message) {
        if(!uart1_initialized){
            initMessenger();
        }
        
        UART1_VIRTUAL.println(message.c_str());
    }
    
    std::string receiveMessage(int verbose, int timeout) {
        String msg = ""; // static so it persists between calls
        unsigned long startTime = millis();

        if(!uart1_initialized){
            initMessenger();
        }

        UART1_VIRTUAL.setTimeout(timeout > 0 ? timeout : UART_TIMEOUT);
        msg = UART1_VIRTUAL.readStringUntil('\n');
        msg.trim();
        if (msg.length()==0 && verbose>0) msg = "Timeout";

        return std::string(msg.c_str());
    }

    bool initMessenger(unsigned long baudrate = UART1_BAUDRATE, unsigned int mode = SERIAL_8N1, int tx = UART1_TX, int rx = UART1_RX) {
        UART1_VIRTUAL.begin(baudrate, mode, rx, tx);
        UART1_VIRTUAL.setTimeout(UART_TIMEOUT);
        return uart1_initialized = true;
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