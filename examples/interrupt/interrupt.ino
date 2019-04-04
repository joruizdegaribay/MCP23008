/* 
 * interrupt.ino
 * 
 * This example configure pin 3 of MCP23008 with falling interrupt,
 * and toggle pin 6 output value of MCP23008 when Arduino read the 
 * interrupt pin value.
 * 
 * Created by Jonathan Ruiz de Garibay
 */

#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;

void setup() {

  // configura pin 0 of the Arduino to read the interrupt state
  pinMode(0, INPUT_PULLUP);

  // configure MCP23008 component
  mcp.begin(0x20);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(3, INPUT_PULLUP);
  mcp.enableInterrupt(3, FALLING);
}

void loop() {

  // when the MCP23008 interrupt pin state is 1
  if (digitalRead(0) == LOW) {
    // read MCP23008 pin values
    unsigned char iovalues = mcp.read();
    // and toogle pin 6 state
    if (bitRead(iovalues, 6) == LOW)
      bitWrite(iovalues, 6, HIGH);
    else
      bitWrite(iovalues, 6, LOW);
    mcp.write(iovalues);
  }
  delay(10);
}
