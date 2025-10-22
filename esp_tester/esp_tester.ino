//Put all files from libraries to the same folder as program
//#include <Arduiono.h>
#include <vscp.hpp>
#include <expt.hpp>

void setup() {
  // put your setup code here, to run once:
  initLogger();

  logMessage("ESP Tester started");
}

void handle_input(String input) {
  input.toLowerCase();
  // is "init" in the input?
  if (input.indexOf("init") != -1) {
    logMessage("Initialization command received");
    // Add initialization code here
    sendMessage("?status=1");
  }
}

void loop() {
  // Read the Serial input
  String input = String(receiveMessage());
  logMessage("?status=1");
  //handle_input(input);
  //Serial.print("Received: ");
  //Serial.println(input);

  delay(10);
}
