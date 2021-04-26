#ifndef _PROMETEO_SENSORS_H_
#define _PROMETEO_SENSORS_H_

#include <Wire.h>

#define T9602_ADDRESS 0x28 //This is the 7-bit I2C address of the Telaire T9602
#define ATLAS_SCIENTIFIC_DO_ADDRESS 0x61 //This is the 7-bit I2C address of the Atlas Scientific DO

class T9602
{
    public:
        T9602(void);
        bool begin(TwoWire &wirePort = Wire);
        bool isConnected();
        float readRelativeHumidity();
        float readTemperature();

    private:
        TwoWire * _i2cPort;

};

class AtlasScientificDO
{
public:
    AtlasScientificDO(void);
    bool begin(TwoWire &wirePort = Wire);
    bool isConnected();
    float readDissolvedOxygen();

private:
    TwoWire * _i2cPort;

};

#endif //_PROMETEO_SENSORS_H_
