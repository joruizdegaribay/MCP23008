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

void MCP23008::pinMode(uint8_t mode) {
	
	// write the new IODIR
	_write(MCP23008_IODIR, mode);
}

void MCP23008::pinMode(uint8_t pin, uint8_t mode) {
	
	uint8_t iodir = _read(MCP23008_IODIR);
	if (mode == OUTPUT)
		bitWrite(iodir, pin, 0);
	else{
		bitWrite(iodir, pin, 1);
		uint8_t pullup = _read(MCP23008_GPPU);
		if (mode == INPUT_PULLUP)
			bitWrite(pullup, pin, 1);
		else
			bitWrite(pullup, pin, 0);
		_write(MCP23008_GPPU, pullup);
	}
	// write the new IODIR
	_write(MCP23008_IODIR, iodir);
}

void MCP23008::setPullup(uint8_t pullup) {
	
	// write pullup values
	_write(MCP23008_GPPU, pullup);
}

uint8_t MCP23008::read(){

	return _read(MCP23008_GPIO);
}

uint8_t MCP23008::read(uint8_t pin){
	
	uint8_t gpio = _read(MCP23008_GPIO);
	return bitRead(gpio, pin);
}

void MCP23008::write(uint8_t values){

	_write(MCP23008_GPIO, values);
}

void MCP23008::write(uint8_t pin, uint8_t value){

	uint8_t gpio = _read(MCP23008_GPIO);
	bitWrite(gpio, pin, value);
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