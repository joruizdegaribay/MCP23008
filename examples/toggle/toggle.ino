/* 
 * toggle.ino
 * 
 * This example blink a LED conected in pin 6 of the MCP23008 component.
 * 
 * Created by Jonathan Ruiz de Garibay
 */
 
#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;

void setup() {  

  // configure MCP23008 component
  mcp.begin(0x20);
  mcp.pinMode(6, OUTPUT);
}

void loop() {

  mcp.write(6, HIGH);     // turn on MCP23008 pin 6
  delay(1000);
  mcp.write(6, LOW);      // turn off MCP23008 pin 6
  delay(1000);
}
