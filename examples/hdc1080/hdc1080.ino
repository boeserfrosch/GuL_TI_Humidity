#include <Arduino.h>
#include <HDC1080.h>
#include <Wire.h>

GuL::HDC1080 hdc(Wire);

std::string outputFormat = "Tempeprature\t= %.6f degC \n"
                           "Humidity\t= %.6f %% \n"
                           "\n";

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    hdc.resetConfiguration();
    hdc.enableHeater();
    hdc.setHumidityResolution(GuL::HDC1080::HumidityMeasurementResolution::HUM_RES_14BIT);
    hdc.setTemperaturResolution(GuL::HDC1080::TemperatureMeasurementResolution::TEMP_RES_14BIT);
    hdc.setAcquisitionMode(GuL::HDC1080::AcquisitionModes::BOTH_CHANNEL);
}

void loop()
{
    hdc.startAcquisition(GuL::HDC1080::Channel::BOTH);
    delay((hdc.getConversionTime(GuL::HDC1080::Channel::BOTH) / 1000) + 1);

    float temperature = hdc.getTemperature();
    float humidity = hdc.getHumidity();

    Serial.printf(outputFormat.c_str(), temperature, humidity);
}