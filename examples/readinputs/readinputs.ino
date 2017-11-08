#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;

unsigned char iodir[8] = {INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT};
unsigned char iovalues[8];
  
void setup() {  

  Serial.begin(9600);
  
  mcp.begin(0x20);

  mcp.pinMode(iodir);

}

void loop() {

  mcp.read(iovalues);

  for (int i = 7; i >= 0; i--){
    Serial.print(iovalues[i]);
  }
  Serial.println();
  delay(100);
}
