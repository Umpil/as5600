#include "ENCODER.h"


ENCODER::ENCODER(TwoWire* wire)
{
	_wire = wire;
}

int16_t ENCODER::ReadData(uint8_t regist)
{
	_wire->beginTransmission(ADRESS);
	_wire->write(regist);
	_wire->endTransmission();
	_wire->requestFrom(ADRESS, (uint8_t)2);
	uint16_t recieved_data = _wire->read();
	recieved_data << 8;
	recieved_data += Wire.read();
	recieved_data = recieved_data & 0x0FFF;
	return recieved_data;
}
uint16_t ENCODER::GetAngle()
{
	uint16_t value = ReadData(ANGLE_WIRE);
	if (ROTATION == 0)
	{
		value = (4096 - value) & 0x0FFF;
	}
	return value;
}

uint16_t ENCODER::GetRawAngle()
{
	uint16_t value = ReadData(RAW_ANGLE_WIRE);
	if (ROTATION == 0)
	{
		value = (4096 - value) & 0x0FFF;
	}
	return value;
}

void ENCODER::SetDirection(int dir = 0)
{
	if (dir == 0)
	{
		ROTATION = 0;
	}
	else
	{
		ROTATION = 1;
	}
}




