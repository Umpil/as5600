#pragma once


#include "Arduino.h"
#include "Wire.h"


// SDA to SDA
// SCL to SCL
// VCC to 3.3v
// GND to DNG

//ARDUINO CODE 
//#include <Wire.h>
//#include "this package"
//IN SETUP()
//Wire.begin()



const uint8_t  ANGLE_WIRE = 0x0F;
const uint8_t RAW_ANGLE_WIRE = 0x0D;
const uint8_t ADRESS = 0x36;



class ENCODER
{
public:
	ENCODER(TwoWire* wire = &Wire);
	uint16_t GetAngle();
	uint16_t GetRawAngle();
	void SetDirection(int dir);
	int ROTATION = 0;

private:
	int16_t ReadData(uint8_t regist);
	TwoWire* _wire;
};