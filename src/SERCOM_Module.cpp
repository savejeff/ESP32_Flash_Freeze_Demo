#include "SERCOM_Module.h"


jSerialHard jSerial0(Serial);
jSerialHard jSerial1(Serial1);
jSerialHard jSerial2(Serial2);


jI2C_Soft _I2C0(21, 22);


jSPI_Hard SPI0(&SPI, 18, 19, 23);
