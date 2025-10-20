//Put all files from libraries to the same folder as program
#include "config.hpp"
#include "manager.hpp"
//#include <Arduiono.h>

SensorManager Manager = SensorManager();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  Manager.init(false);
  Manager.print();

  Manager.reconstruct();
}

void loop() {
  // put your main code here, to run repeatedly:
  Manager.resync();
  delay(50);
  Manager.redraw();
  delay(2500);
  //Manager.print();
}
