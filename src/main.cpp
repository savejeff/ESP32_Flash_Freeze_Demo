#include "Arduino.h"

#include "EEPROM.h"
#include "SD.h"
#include "SD_MMC.h"
#include "SPIFFS.h"
#include <esp_task_wdt.h>

/********************************************/


//#include <SERCOM_Module.h>

// REMOVE THIS AND FREEZES GO AWAY
String XXXX = "XXXXXXXXXXXXXXXXXXX";
String XXXX2 = "XXXXXXXXXXXXXXXXXXX";
String XXXX3 = "XXXXXXXXXXXXXXXXXXX";
String XXXX4 = "XXXXXXXXXXXXXXXXXXX";
String XXXX5 = "XXXXXXXXXXXXXXXXXXX";
String XXXX6 = "XXXXXXXXXXXXXXXXXXX";
String XXXX7 = "XXXXXXXXXXXXXXXXXXX";
String XXXX8 = "XXXXXXXXXXXXXXXXXXX";



/**********************************************/

#define _PIN_LED 25

//#define WAIT_4_SERIAL

void setup() 
{
	// init led pin
	pinMode(_PIN_LED, OUTPUT);
	digitalWrite(_PIN_LED, HIGH);
	delay(100);
	digitalWrite(_PIN_LED, LOW);
	

	Serial.begin(115200);
#ifdef WAIT_4_SERIAL
	Serial.println("Starting - press any key");

	// wait for serial input 
	while(!Serial.available())
	{
		Serial.print(".");
		delay(500);
		digitalWrite(_PIN_LED, HIGH);
		delay(500);
		digitalWrite(_PIN_LED, LOW);
	}
	while(Serial.available())
		Serial.read();
	Serial.println();
#endif // WAIT_4_SERIAL
	

	Serial.println("SPIFFS init"); Serial.flush();
		
	SPIFFS.begin(true);

	Serial.println("SPIFFS init done"); Serial.flush();

	
	EEPROM.begin(512);
	
	uint8_t c = 0;
	while (true)
	{	
		digitalWrite(_PIN_LED, HIGH);

		Serial.printf(">>>> WRITE %d\n", c); Serial.flush();

		EEPROM.writeByte(0x8C, c++);
		EEPROM.commit();	

		digitalWrite(_PIN_LED, LOW);

		delay(1000);

	}
}

void loop() {

}