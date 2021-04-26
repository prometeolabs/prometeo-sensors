#include "prometeo_sensors.h"
#include <arduino.h>

T9602::T9602()
{
    //Constructor
}

bool T9602::begin(TwoWire &wirePort)
{
    _i2cPort = &wirePort;   //Grab which port the user wants us to use
    _i2cPort->begin();
}

bool T9602::isConnected()
{
    _i2cPort->beginTransmission((uint8_t)T9602_ADDRESS);
    if (_i2cPort->endTransmission() == 0){
        return true;
    }else{
        return false;
    }
}

float T9602::readRelativeHumidity()
{
    byte data[2];
    float relativeHumidity;

    _i2cPort->beginTransmission((uint8_t)T9602_ADDRESS);
    _i2cPort->write(0x00);                      //Read only upper 2 data bytes
    _i2cPort->endTransmission();

    _i2cPort->requestFrom(T9602_ADDRESS, 2);    // Request 4 byte
    data[0] = _i2cPort->read();
    data[1] = _i2cPort->read();

    // humidity = (rH_High [5:0] x 256 + rH_Low [7:0]) / 16384 x 100
    relativeHumidity = (float)(((data[0] & 0x3F ) << 8) + data[1]) / 16384.0 * 100.0;

    return (relativeHumidity);
}

float T9602::readTemperature()
{
    byte data[2];
    float temperature;

    _i2cPort->beginTransmission((uint8_t)T9602_ADDRESS);
    _i2cPort->write(0x02);                      //Read only upper 2 data bytes
    _i2cPort->endTransmission();

    _i2cPort->requestFrom(T9602_ADDRESS, 2);    // Request 4 byte
    data[0] = _i2cPort->read();
    data[1] = _i2cPort->read();

    // temperature = (Temp_High [7:0] x 64 + Temp_Low [7:2]/4 ) / 16384 x 165 - 40
    temperature = (float)((unsigned)(data[0]  * 64) + (unsigned)(data[1] >> 2 )) / 16384.0 * 165.0 - 40.0;

    return (temperature);
}


AtlasScientificDO::AtlasScientificDO()
{
    //Constructor
}

bool AtlasScientificDO::begin(TwoWire &wirePort)
{
    _i2cPort = &wirePort;   //Grab which port the user wants us to use
    _i2cPort->begin();
}

bool AtlasScientificDO::isConnected()
{
    _i2cPort->beginTransmission((uint8_t)T9602_ADDRESS);
    if (_i2cPort->endTransmission() == 0){
        return true;
    }else{
        return false;
    }
}

float AtlasScientificDO::readDissolvedOxygen()
{
    byte data[20];
    byte incoming_char = 0;
    float dissolvedOxygen;
    int i = 1;

    _i2cPort->beginTransmission((uint8_t)ATLAS_SCIENTIFIC_DO_ADDRESS);
    _i2cPort->write('r');                      //Read only upper 2 data bytes
    _i2cPort->endTransmission();

    delay(575);

    _i2cPort->requestFrom(ATLAS_SCIENTIFIC_DO_ADDRESS, 2);    // Request 4 byte
    data[0] = _i2cPort->read();

    switch (data[0]) {                              //switch case based on what the response code is.
        case 1:                                     //decimal 1.
            break;                                  //means the command was successful.

        case 2:                                     //decimal 2.
            return (-502);                          //means the command has failed.
            break;                                  //exits the switch case.

        case 254:                                   //decimal 254.
            return (-503);                          //means the command has not yet been finished calculating.
            break;                                  //exits the switch case.

        case 255:                                   //decimal 255.
            return (-504);                          //means there is no further data to send.
            break;                                  //exits the switch case.
    }

    while (_i2cPort->available()) {                 //are there bytes to receive.
        incoming_char = _i2cPort->read();
        data[i] = incoming_char;                    //load this byte into our array.
        i += 1;                                  //incur the counter for the array element.
        if (incoming_char == 0) {                      //if we see that we have been sent a null command.
            i = 0;                                 //reset the counter i to 0.
            break;                                 //exit the while loop.
        }
    }

    return (200);
}