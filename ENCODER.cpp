#include "ENCODER.h"

//Get Wire class
//Wire.begin()
ENCODER::ENCODER(TwoWire* wire)
{
	_wire = wire;
}

//Take 2byte data from raw angle and angle
uint16_t ENCODER::ReadData(uint8_t regist)
{
	uint16_t recieved_data;

	_wire->beginTransmission(ADRESS);
	_wire->write(regist);
	_wire->endTransmission();
	_wire->requestFrom(ADRESS, (uint8_t)2);
	while (_wire->available() == 0);

	recieved_data += _wire->read();
	recieved_data = recieved_data << 8;

	while (_wire->available() == 0);

	recieved_data += _wire->read();

	return recieved_data;
}

//Get angle as arrray of 2 bytes
uint8_t* ENCODER::GetAngleBytes()
{
	static uint8_t value[2];
	uint16_t data_int;

	data_int = ReadData(ANGLE_WIRE_H) & 0x0FFF;
	if (ROTATION == 1)
	{
		data_int = (0x1000 - data_int) & 0x0FFF;
	}
	value[0] = (data_int >> 8) & 0xFF;
	value[1] = data_int & 0xFF;
	return value;
}

//Get angle as 2byte int
uint16_t ENCODER::GetAngle()
{
	uint16_t data_int;
	data_int = ReadData(ANGLE_WIRE_H) & 0x0FFF;
	if (ROTATION == 1)
	{
		data_int = (0x1000 - data_int) & 0x0FFF;
	}
	return data_int;
}

//Get angle as degrees
uint16_t ENCODER::GetDegrees()
{
	uint16_t data = GetAngle();
	float degrees = (float)data * ANGLE_TO_DEGREES;
	return degrees;

}

//Get raw angle as array of 2 bytes
uint8_t* ENCODER::GetRawAngleBytes()
{
	static uint8_t value[2];
	uint16_t data_int;
	data_int = ReadData(RAW_ANGLE_WIRE_H) & 0x0FFF;
	if (ROTATION == 1)
	{
		data_int = (0x1000 - data_int) & 0x0FFF;
	}
	value[0] = (data_int >> 8) & 0xFF;
	value[1] = data_int & 0xFF;
	return value;
}

//Get raw angle as 2byte int
uint16_t ENCODER::GetRawAngle()
{
	uint16_t data_int;
	data_int = ReadData(RAW_ANGLE_WIRE_H) & 0x0FFF;
	if (ROTATION == 1)
	{
		data_int = (0x1000 - data_int) & 0x0FFF;
	}
	return data_int;
}

//Get magnet status
//2 - magnet is too strong
//1 - magnet is ok
//0 - magnet is too weak or not detected
int8_t ENCODER::CheckMagnet()
{
	uint8_t result;

	_wire->beginTransmission(ADRESS);
	_wire->write(MAGNET_WIRE);
	if (_wire->endTransmission() != 0)
	{
		return CheckMagnet();
	}
	_wire->requestFrom(ADRESS, (uint8_t)1);
	while (Wire.available() == 0);
	result = _wire->read();
	switch (result)
	{
		//ok
	case 0x37:
		return 0x01;
		break;
		//strong
	case 0x27:
		return 0x02;
		break;
		//weak
	case 0x17:
		return 0x00;
		break;
	default:
		break;
	}

}

//Optional set direction to value
void ENCODER::SetDirection(int dir = 0)
{
	if (dir == 0)
	{
		// TO -
		ROTATION = 0;
	}
	else
	{
		// TO +
		ROTATION = 1;
	}
}




