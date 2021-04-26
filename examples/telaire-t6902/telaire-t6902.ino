#include <prometeo_sensors.h>

T9602 t9602Sensor;

bool error = false;
unsigned long sampleRate = 1000;     // 5 second dust sample rate
unsigned long sampleTime;           // variable to monitor time of each sample start

float temperatureValue;
float humidityValue;


void setup()
{
    t9602Sensor.begin();
    Serial.begin(9600);

    error = t9602Sensor.isConnected();
    if (error == true)
    {
        Serial.println("error - t9602 connection error");
    }else
    {
        Serial.println("info - t9602 connection success");
    }
}


void loop()
{
    if (millis() >= (sampleRate + sampleTime))
    {
        if (t9602Sensor.isConnected() == true)
        {
            temperatureValue = t9602Sensor.readTemperature();
            humidityValue = t9602Sensor.readRelativeHumidity();
            Serial.print("info - temperature: ");
            Serial.println(temperatureValue);
            Serial.print("info - relative humidity: ");
            Serial.println(humidityValue);
        }

        sampleTime = millis();      //resets timer before printing output
    }
}