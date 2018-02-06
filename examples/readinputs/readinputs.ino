#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;
  
void setup() {  

  Serial.begin(9600);
  
  mcp.begin(0x27);
  mcp.pinMode(0xFF);
  mcp.setPullup(0x0F);
}

void loop() {

  unsigned char iovalues = mcp.read();
  Serial.println(iovalues, BIN);
  delay(100);
}
