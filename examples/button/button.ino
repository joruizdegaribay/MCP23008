/* 
 * button.ino
 * 
 * This example read the state of pin 3 (configurated as input pin 
 * with pull-up resistor) and copies its state in the LED_BUILTIN 
 * of the Arduino board.
 * 
 * Created by Jonathan Ruiz de Garibay
 */
 
#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;

void setup() {

  // configure MCP23008 component
  mcp.begin(0x20);
  mcp.pinMode(3, INPUT_PULLUP);

  // configure Arduino LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);  // use the p13 LED as debugging
}

void loop() {

  // read MCP23008 pin 3 state
  unsigned char value = mcp.read(3);

  // and copy in LED_BUILTIN pin
  digitalWrite(LED_BUILTIN, value);
}
