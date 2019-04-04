/* 
 * readinputs.ino
 * 
 * This example read status pins (configurated as inputs with pull-up
 * resistors) and send them over the serial port in binary mode.
 * 
 * Created by Jonathan Ruiz de Garibay
 */

#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;
  
void setup() {  

  // init serial port
  Serial.begin(9600);
  
  // configure MCP23008 component
  mcp.begin(0x20);
  mcp.pinMode(0xFF);
  mcp.setPullup(0xFF);
}

void loop() {

  // read MCP23008 pin values
  unsigned char iovalues = mcp.read();
  // and send by serial port in binary mode
  Serial.println(iovalues, BIN);
  delay(100);
}
