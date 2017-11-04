/*************************************************** 
  This is a library for the MCP23008 i2c port expander
 ****************************************************/

#include "MCP23008.h"

#include <Wire.h>

void MCP23008::begin(uint8_t address) {
	
	_i2cAddress = address;

	Wire.begin();

	// set defaults!
	Wire.beginTransmission(_i2cAddress);
	Wire.write((byte)MCP23008_IODIR);
	Wire.write((byte)0xFF);  // all inputs
	Wire.write((byte)0x00);
	Wire.write((byte)0x00);
	Wire.write((byte)0x00);
	Wire.write((byte)0x06);
	Wire.write((byte)0x00);
	Wire.write((byte)0x00);
	Wire.write((byte)0x00);
	Wire.write((byte)0x00);
	Wire.write((byte)0x00);	
	Wire.endTransmission();
}

void MCP23008::pinMode(byte mode[8]) {
	
	uint8_t iodir = 0x00, gppu = 0x00;
	for (int pin = 0; pin < 8; pin++){
		// set the pin and direction
		if (mode[pin] != OUTPUT)
			bitSet(iodir, pin);
		// set the pullup
		if (mode[pin] == INPUT_PULLUP)
			bitSet(gppu, pin);
	}
	// write the new IODIR
	_write(MCP23008_IODIR, iodir);
	// write pullup values
	_write(MCP23008_GPPU, gppu);
}

void MCP23008::read(byte values[8]){

	uint8_t gpio = _read(MCP23008_GPIO);
	for (int pin = 0; pin < 8; pin++){
		values[pin] = bitRead(gpio, pin);
	}
}

void MCP23008::write(byte values[8]){

	uint8_t gpio;
	for (int pin = 0; pin < 8; pin++){
		bitWrite(gpio, pin, values[pin]);
	}
	_write(MCP23008_GPIO, gpio);

}

void MCP23008::enableInterrupt(uint8_t pin, uint8_t mode){
	
	uint8_t gpinten, defval, intcon;

	gpinten =_read(MCP23008_GPINTEN);
	defval = _read(MCP23008_DEFVAL);
	intcon = _read(MCP23008_INTCON);

	bitSet(gpinten, pin);
	switch (mode)
	{
		case CHANGE:
			bitClear(intcon, pin);
			break;
		case RISING:
			bitSet(intcon, pin);
			bitClear(defval, pin);
			break;
		case FALLING:
			bitSet(intcon, pin);
			bitSet(defval, pin);
			break;
	}

	_write(MCP23008_GPINTEN, gpinten);
	_write(MCP23008_DEFVAL, defval);
	_write(MCP23008_INTCON, intcon);
}

void MCP23008::disableInterrupt(uint8_t pin){

	uint8_t gpinten =_read(MCP23008_GPINTEN);

	bitClear(gpinten, pin);
	
	_write(MCP23008_GPINTEN, gpinten);
}

uint8_t MCP23008::_read(uint8_t address) {
	
	Wire.beginTransmission(MCP23008_ADDRESS | _i2cAddress);
	Wire.write((byte)address);	
	Wire.endTransmission();
	Wire.requestFrom(MCP23008_ADDRESS | _i2cAddress, 1);
	return Wire.read();
}

void MCP23008::_write(uint8_t addr, uint8_t data) {
	
	Wire.beginTransmission(MCP23008_ADDRESS | _i2cAddress);
	Wire.write((byte)addr);
	Wire.write((byte)data);
	Wire.endTransmission();
}