/**
 * @file messenger.hpp
 * @brief Declaration of the messenger interface and related global functions.
 * 
 * This header declares the global functions for message operations. It includes configuration
 * and exception handling support.
 * 
 * @copyright 2024 MTA
 * @author 
 * Ing. Jiri Konecny
 */

#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <string>
#include "../config.hpp"     ///< Configuration.

#ifdef ARDUINO_H
    #include <Arduino.h>  ///< Include Arduino Serial functions
#elif defined(STDIO_H)
    #include <stdio.h>    ///< Include standard I/O functions
#endif

/**
* @brief Initializes the global messenger.
* 
* @param baudrate The baudrate for the messenger.
* @param mode The mode for the messenger.
* @param tx The transmit pin for the messenger.
* @param rx The receive pin for the messenger.
* @param port The UART port for the messenger.
* @throws Exception if initialization fails.
*/
bool initMessenger(unsigned long baudrate, unsigned int mode, int rx, int tx, unsigned int port);

/**
 * @brief Initializes the global messenger - automatic configuration.
 * 
 * @throws Exception if initialization fails.
 */
bool initMessenger();

/**
 * @brief Sends a message using the global messenger.
 * 
 * @param message The message to send.
 * @throws Exception if sending fails.
 */
void sendMessage(const char* message);

/**
 * @brief Sends a message using the global messenger.
 * 
 * @param message The message to send.
 * @throws Exception if sending fails.
 */
void sendMessage(const std::string &message);

#ifdef ARDUINO_H
/**
 * @brief Sends a message using the global messenger.
 * 
 * @param message The message to send.
 * @throws Exception if sending fails.
 */
void sendMessage(const String &message);
#endif

/**
 * @brief Receives a message using the global messenger.
 * 
 * @param timeout The timeout in milliseconds to wait for a message.
 * @param verbose Verbosity level for logging (0 = silent, 1 = errors, 2 = all).
 * @return A C-string containing the received message.
 * @throws Exception if receiving fails.
 */
const char* receiveMessageAsChars(int verbose = 0, int timeout = UART1_TIMEOUT);

/**
 * @brief Receives a message using the global messenger.
 * 
 * @param timeout The timeout in milliseconds to wait for a message.
 * @param verbose Verbosity level for logging (0 = silent, 1 = errors, 2 = all).
 * @return A string containing the received message.
 * @throws Exception if receiving fails.
 */
std::string receiveMessage(int verbose = 0, int timeout = UART1_TIMEOUT);

#ifdef ARDUINO_H
/**
 * @brief Receives a message using the global messenger.
 * 
 * @param timeout The timeout in milliseconds to wait for a message.
 * @param verbose Verbosity level for logging (0 = silent, 1 = errors, 2 = all).
 * @return An Arduino String containing the received message.
 * @throws Exception if receiving fails.
 */
String receiveMessageAsString(int verbose = 0, int timeout = UART1_TIMEOUT);
#endif

#endif // MESSENGER_HPP
