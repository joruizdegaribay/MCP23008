#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;

unsigned char iodir[8] = {INPUT_PULLUP, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT};
unsigned char iovalues[8];
  
void setup() {  

  mcp.begin(0x20);

  mcp.pinMode(iodir);

  pinMode(13, OUTPUT);  // use the p13 LED as debugging
}

void loop() {

  mcp.read(iovalues);

  // The LED will 'echo' the button
  digitalWrite(13, iovalues[0]);
}
