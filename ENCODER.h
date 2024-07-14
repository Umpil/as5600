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



//const uint8_t ANGLE_WIRE_L = 0x0F;
const uint8_t ANGLE_WIRE_H = 0x0E;
//const uint8_t RAW_ANGLE_WIRE_L = 0x0D;
const uint8_t RAW_ANGLE_WIRE_H = 0x0C;
const uint8_t ADRESS = 0x36;
const uint8_t MAGNET_WIRE = 0x0B;
const float ANGLE_TO_DEGREES = 360/4096;



class ENCODER
{
public:
	uint16_t GetAngle();
	uint16_t GetRawAngle();
	uint16_t GetDegrees();
	ENCODER(TwoWire* wire = &Wire);
	uint8_t *GetAngleBytes();
	uint8_t *GetRawAngleBytes();
	void SetDirection(int dir);
	int ROTATION = 0;
	int8_t CheckMagnet();

private:
	uint16_t ReadData(uint8_t register);
	TwoWire* _wire;
};