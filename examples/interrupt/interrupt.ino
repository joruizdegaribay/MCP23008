#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;

unsigned char iodir[8] = {INPUT_PULLUP, OUTPUT, INPUT, INPUT, INPUT, INPUT, INPUT, INPUT};
unsigned char iovalues[8];

void setup() {

  pinMode(0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(0), button, FALLING);
  pinMode(13, OUTPUT);

  mcp.begin(0x20);
  mcp.pinMode(iodir);
  mcp.enableInterrupt(0, FALLING);
}

void loop() {

  mcp.read(iovalues);
  if (iovalues[1] == LOW)
    iovalues[1] = HIGH;
  else
    iovalues[1] = LOW;
  mcp.write(iovalues);
  delay(1000);
}

void button() {

  if (digitalRead(13) == LOW)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
}

