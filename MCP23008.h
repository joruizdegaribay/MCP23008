/*************************************************** 
  This is a library for the MCP23008 i2c port expander
 ****************************************************/

#ifndef MCP23008_H
#define MCP23008_H

#include "Arduino.h"

#define MCP23008_ADDRESS 	0x20

#define MCP23008_IODIR 		0x00
#define MCP23008_IPOL 		0x01
#define MCP23008_GPINTEN 	0x02
#define MCP23008_DEFVAL 	0x03
#define MCP23008_INTCON 	0x04
#define MCP23008_IOCON 		0x05
#define MCP23008_GPPU 		0x06
#define MCP23008_INTF 		0x07
#define MCP23008_INTCAP 	0x08
#define MCP23008_GPIO 		0x09
#define MCP23008_OLAT 		0x0A

#define NO_INTERRUPT		0x00

#endif

class MCP23008 {

	public:
		void begin(uint8_t addr);
		void pinMode(uint8_t mode);
		void pinMode(uint8_t pin, uint8_t mode);
		void setPullup(uint8_t pullup);
		uint8_t read();
		uint8_t read(uint8_t pin);
		void write(uint8_t values);
		void write(uint8_t pin, uint8_t value);
		void enableInterrupt(uint8_t pin, uint8_t mode);
		void disableInterrupt(uint8_t pin);

	private:
		uint8_t _i2cAddress;
		uint8_t _read(uint8_t addr);
		void _write(uint8_t addr, uint8_t data);
};
