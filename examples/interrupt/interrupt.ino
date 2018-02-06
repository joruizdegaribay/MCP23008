#include <Wire.h>
#include "MCP23008.h"

MCP23008 mcp;

void setup() {

  pinMode(0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(0), button, FALLING);
  pinMode(13, OUTPUT);

  mcp.begin(0x27);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(3, INPUT_PULLUP);
  mcp.enableInterrupt(0, FALLING);
}

void loop() {

  unsigned char iovalues = mcp.read();
  if (bitRead(iovalues, 6) == LOW)
    bitWrite(iovalues, 6, HIGH);
  else
    bitWrite(iovalues, 6, LOW);
  mcp.write(iovalues);
  delay(1000);
}

void button() {

  if (digitalRead(13) == LOW)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
}

