#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;

unsigned char iodir[8] = {OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT};
unsigned char iovalues[8];
  
void setup() {  

  mcp.begin(0x20);      // use default address 0x20
  mcp.pinMode(iodir);
}


// flip the pin #0 up and down

void loop() {

  iovalues[0] = HIGH;
  mcp.write(iovalues);
  delay(1000);
  iovalues[0] = LOW;
  mcp.write(iovalues);
  delay(1000);
}
