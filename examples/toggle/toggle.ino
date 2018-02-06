#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;

void setup() {  

  mcp.begin(0x27);      // use default address 0x20
  mcp.pinMode(6, OUTPUT);
}


// flip the pin #0 up and down

void loop() {

  mcp.write(6, HIGH);
  delay(1000);
  mcp.write(6, LOW);
  delay(1000);
}
