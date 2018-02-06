#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;
  
void setup() {  

  mcp.begin(0x27);

  mcp.pinMode(3, INPUT_PULLUP);
  
  pinMode(13, OUTPUT);  // use the p13 LED as debugging
}

void loop() {

  unsigned char value = mcp.read(3);

  // The LED will 'echo' the button
  
  digitalWrite(13, value);
}
