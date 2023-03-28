#pragma once

#include "Arduino.h" 


class jSerialHard : public Stream
{

protected:
	Stream* stream = nullptr;	
	HardwareSerial* ser = nullptr;

	int8_t _pin_tx=-1;
	int8_t _pin_rx=-1;
	uint32_t _baud = 115200;

public:
	
	jSerialHard(HardwareSerial& serial) 
	: ser(&serial)
	{ 
		stream = ser;
	}

	jSerialHard(HardwareSerial& serial, int8_t txPin, int8_t rxPin) 
	: ser(&serial)
	{ 
		stream = ser;
		_pin_tx = txPin;
		_pin_rx = rxPin;
	}

	void begin() {
		begin(_baud);
	}
	
	void begin(uint32_t baud) { }

	void end() {}

	int available() { return 0; }
	int read() { return 0; }
	int peek() { return 0; }
	
	virtual void flush() {  }
	virtual size_t write(uint8_t c) { return 0; }	
	virtual size_t write(const uint8_t *buffer, size_t size) {	return 0;	}
	virtual size_t print(const String &s) { return 0; }
	virtual size_t print(char c){return 0;}
};


class jSPI_Port_Base {

public:
	
	jSPI_Port_Base() { }

	virtual void begin() = 0;
	virtual void end() = 0;
	
	virtual void beginTransaction() = 0;
	virtual void endTransaction(void) = 0;
	
};

class jSPI
{
protected:
	jSPI_Port_Base* _jspi_port;
	uint8_t _pin_cs = -1;

	uint32_t _freq = 1E6;
	

public:
	jSPI(jSPI_Port_Base* jspi_port, uint8_t pin_cs)
		: _jspi_port(jspi_port), _pin_cs(pin_cs)
	{

	}

	virtual void begin() {}
	virtual void end() {}
	virtual void beginTransaction() {}
	virtual void endTransaction(void) { }
};



/**************************************************************************/


#include "SPI.h"


class jSPI_Hard : public jSPI_Port_Base
{
protected:

	SPIClass* _spi = &SPI;

	int8_t pin_sck = -1;
	int8_t pin_miso = -1;
	int8_t pin_mosi = -1;


public:

	jSPI_Hard(SPIClass* _SPI)
	{
		_spi = _SPI;
	}
	
	jSPI_Hard(SPIClass* _SPI, int8_t sck, int8_t miso, int8_t mosi)
	 : pin_sck(sck), pin_miso(miso), pin_mosi(mosi)
	{
		_spi = _SPI;
	}

	void begin(int8_t sck, int8_t miso, int8_t mosi){}
	void begin() {}
	void end(){}
	void beginTransaction() override {}
	void endTransaction(void) {}
	
};


class jI2C_base
{

public:
	jI2C_base() { }
	virtual void begin() = 0;
	virtual void end() = 0;

	virtual void setFrequency(uint32_t freq) = 0;
	virtual void beginTransmission(uint8_t addr) = 0;
	virtual uint8_t endTransmission(bool stopBit) = 0;
	virtual uint8_t endTransmission(void) = 0;
	
};



class jI2C_Soft : public jI2C_base
{
protected:

	uint8_t _pin_sda = -1;
	uint8_t _pin_scl = -1;

public:

	jI2C_Soft(uint8_t pin_sda, uint8_t pin_scl)
	{
		_pin_sda = pin_sda;
  		_pin_scl = pin_scl;
	}
	void begin(){}
	void end(){}
	
	void setFrequency(uint32_t freq){}

	void beginTransmission(uint8_t addr){}
	uint8_t endTransmission(bool stopBit){return 0;}
	uint8_t endTransmission(void){return 0;}
};
