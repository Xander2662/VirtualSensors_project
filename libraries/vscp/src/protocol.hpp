
// Define class Protocol for handling API communication protocol
// API protocol is URL-like with key-value pairs separated by '&' and '=', starting with '?' for request
// API response is in same format with key-value pairs
//API methods:
/*
- init: handshake and ensure purpose of application, matches device db versions and api versions
req: ?type=INIT&app=APP_NAME&version=APP_VERSION&dbversion=DB_VERSION&api=API_VERSION
res: ?status=1/0&error=Error Message
- update: request data update
req: ?type=UPDATE&id=UID
res: ?id=UID&status=1/0/-1&param1=value1&param2=value2...
- config: send new configuration for sensor from HMI side to HW side
req: ?type=CONFIG&id=UID&param1=value1&param2=value2
res: ?id=UID&status=1/0/-1&error=Error Message
- reset: reset the sensor
req: ?type=RESET&id=UID
res: ?id=UID&status=1/0/-1&error=Error Message
- connect: connect sensor to pin
req: ?type=CONNECT&id=UID&pin=PIN
res: ?id=UID&status=1/0/-1&error=Error Message
- disconnect: disconnect sensor from pin
req: ?type=DISCONNECT&id=UID
res: ?id=UID&status=1/0/-1&error=Error Message
*/
// Create class method for every API method
// For sending/receiving messages, use abstracted messenger interface - Messenger, user can connect to own implementation in .cpp file
// Messenger interface should be implemented for different platforms (Arduino, stdio, etc.)


/**
 * @file protocol.hpp
 * @brief Declaration of the Protocol class for handling API communication protocol.
 * 
 * This header defines the Protocol class that manages the communication protocol for sensor operations.
 * It includes methods for initializing, updating, configuring, resetting, connecting, and disconnecting sensors.
 * The protocol follows a URL-like format with key-value pairs.
 * Each method corresponds to a specific API request and response format.
 * The Protocol class interacts with the Messenger interface for communication.
 */

#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "config.hpp"
#include "io/messenger.hpp"
#include "exceptions/exceptions.hpp"
#include "exceptions/protocol_exceptions.hpp"
#include "exceptions/data_exceptions.hpp"

#include <string>
#include <unordered_map>
    
/**
 * @class Protocol
 * @brief Handles API communication protocol for sensor operations.
 * 
 * The Protocol class provides static methods for sensor communication using a URL-like format 
 * with key-value pairs. It provides methods for initializing connections, updating sensor data, 
 * configuring sensors, resetting sensors, and managing sensor connections to pins.
 * 
 * API format: URL-like with key-value pairs separated by '&' and '=', starting with '?' for requests.
 * Response format: Same format with key-value pairs including status and error information.
 */
class Protocol {
private:
    static const std::string API_VERSION; ///< API version constant
    static bool initialized;              ///< Protocol initialization status
    
    /**
     * @brief Parses a protocol message into key-value pairs.
     * 
     * @param message The protocol message to parse
     * @return std::unordered_map<std::string, std::string> Parsed key-value pairs
     */
    static std::unordered_map<std::string, std::string> parseMessage(const std::string& message, bool caseSensitive);
    
    /**
     * @brief Builds a protocol message from key-value pairs.
     * 
     * @param params Key-value pairs to build message from
     * @return std::string Formatted protocol message
     */
    static std::string buildMessage(const std::unordered_map<std::string, std::string>& params);

public:

    /**
     * @brief Initializes the protocol connection with default values.
     * 
     * Base initialization method for testing and generic usage that doesn't require
     * platform-specific hooks. Uses default application information.
     * 
     * @param verbose If 0 , exceptions are suppressed and default values returned; if 1 (default), exceptions are thrown
     * @return bool True if initialization successful, false otherwise
     * @throws Exception if communication fails (only when verbose=1)
     */
    static bool init_dummy(int verbose = 1);

    /**
     * @brief Initializes the protocol connection with specified API version.
     * 
     * Initialization method that uses default application name, version, and database version
     * but allows specifying the API version. Useful when only API compatibility needs
     * to be verified.
     * 
     * @param verbose If 0 , exceptions are suppressed and default values returned; if 1 (default), exceptions are thrown
     * @return bool True if initialization successful, false otherwise
     * @throws Exception if communication fails (only when verbose=1)
     */
    static bool init(int verbose = 1);

    /**
     * @brief Initializes the protocol connection with specified database version.
     * 
     * Initialization method that uses default application name and version but allows
     * specifying the database version. Useful when only database compatibility needs
     * to be verified.
     * 
     * @param db_version Database version
     * @param verbose If 0 , exceptions are suppressed and default values returned; if 1 (default), exceptions are thrown
     * @return bool True if initialization successful, false otherwise
     * @throws Exception if communication fails (only when verbose=1)
     */
    static bool init(const std::string& db_version, int verbose = 1);

    /**
     * @brief Initializes the protocol connection with handshake.
     * 
     * Performs handshake to ensure application purpose, matches device database versions
     * and API versions with the remote device. Application info is sent once during initialization.
     * 
     * Request format: ?type=INIT&app=APP_NAME_APP_VERSION&db=DB_VERSION&api=API_VERSION
     * Response format: ?status=1/0&error=Error Message
     * 
     * @param app_name Application name (include version?)
     * @param db_version Database version
     * @param verbose If 0 , exceptions are suppressed and default values returned; if 1 (default), exceptions are thrown
     * @return bool True if initialization successful, false otherwise
     * @throws Exception if communication fails (only when verbose=1)
     */
    static bool init(const std::string& app_name, const std::string& db_version, int verbose = 1);
    
    /**
     * @brief Requests data update for a specific sensor.
     * 
     * Request format: ?type=UPDATE&id=UID
     * Response format: ?id=UID&status=1/0&param1=value1&param2=value2...
     * 
     * @param uid Unique identifier of the sensor
     * @param verbose If 0 (default), exceptions are suppressed and empty map returned; if 1, exceptions are thrown
     * @return std::unordered_map<std::string, std::string> Updated sensor parameters
     * @throws Exception if communication fails or sensor not found (only when verbose=1)
     */
    static std::unordered_map<std::string, std::string> update(const std::string& uid, int verbose = 0);
    
    /**
     * @brief Sends new configuration for sensor from HMI side to HW side.
     * 
     * Request format: ?type=CONFIG&id=UID&param1=value1&param2=value2
     * Response format: ?id=UID&status=1/0&error=Error Message
     * 
     * @param uid Unique identifier of the sensor
     * @param config Configuration parameters to set
     * @param verbose If 0 (default), exceptions are suppressed and false returned; if 1, exceptions are thrown
     * @return bool True if configuration successful, false otherwise
     * @throws Exception if communication fails or invalid configuration (only when verbose=1)
     */
    static bool config(const std::string& uid, const std::unordered_map<std::string, std::string>& config, int verbose = 0);
    
    /**
     * @brief Resets the specified sensor.
     * 
     * Request format: ?type=RESET&id=UID
     * Response format: ?id=UID&status=1/0
     * 
     * @param uid Unique identifier of the sensor
     * @param verbose If 0 (default), exceptions are suppressed and false returned; if 1, exceptions are thrown
     * @return bool True if reset successful, false otherwise
     * @throws Exception if communication fails or sensor not found (only when verbose=1)
     */
    static bool reset(const std::string& uid, int verbose = 0);
    
    /**
     * @brief Connects sensor to specified pin.
     * 
     * Request format: ?type=CONNECT&id=UID&pins=PINS
     * where PINS is a string representing one or more pin numbers, e.g., "5" or "5,6,7"
     * Response format: ?id=UID&status=1/0
     * 
     * @param uid Unique identifier of the sensor
     * @param pins Pin(s) number(s) to connect sensor to
     * @param verbose If 0 , exceptions are suppressed and false returned; if 1 (default), exceptions are thrown
     * @return bool True if connection successful, false otherwise
     * @throws Exception if communication fails or pin unavailable (only when verbose=1)
     */
    static bool connect(const std::string& uid, const std::string& pins, int verbose = 1);
    
    /**
     * @brief Disconnects sensor from its current pin.
     * 
     * Request format: ?type=DISCONNECT&id=UID
     * Response format: ?id=UID&status=1/0
     * 
     * @param uid Unique identifier of the sensor
     * @param verbose If 0 , exceptions are suppressed and false returned; if 1 (default), exceptions are thrown
     * @return bool True if disconnection successful, false otherwise
     * @throws Exception if communication fails or sensor not connected (only when verbose=1)
     */
    static bool disconnect(const std::string& uid, int verbose = 1);
    
    /**
     * @brief Checks if protocol is initialized.
     * 
     * @return bool True if protocol is initialized, false otherwise
     */
    static bool isInitialized();
    
    /**
     * @brief Gets the API version.
     * 
     * @return std::string API version
     */
    static std::string getApiVersion();
};

#endif // PROTOCOL_HPP