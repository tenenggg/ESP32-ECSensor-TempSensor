#include "Arduino.h"
#include "DFRobot_ESP_EC.h"
#include "EEPROM.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// === Pin Definitions ===
#define ONE_WIRE_BUS 23 // The pin where your DS18B20 data wire is connected
#define EC_PIN 34

// === Constants ===
#define ESPADC 1024.0
#define ESPVOLTAGE 5000

DFRobot_ESP_EC ec;

// === Temperature Sensor Setup ===
OneWire oneWire(ONE_WIRE_BUS);  // Create oneWire instance
DallasTemperature tempSensor(&oneWire);  // Create DallasTemperature instance

float voltage, ecValue, temperature = 25.0;

void setup()
{
  Serial.begin(115200);
  EEPROM.begin(32);       // Needed to store calibration K in EEPROM
  ec.begin();             // By default, starts at EEPROM address 10

  tempSensor.begin();     // Initialize the temperature sensor
}

void loop()
{
  static unsigned long timepoint = millis();
  if (millis() - timepoint > 4000U) // Time interval: 1s
  {
    timepoint = millis();

    // === Read Voltage ===
    voltage = analogRead(A0) * (3.3 / 4095.0); // Read voltage from analog pin and convert to volts (for ESP32)
    Serial.print("EC Raw Voltage (V): ");
    Serial.println(voltage, 4);

    // === Read Temperature ===
    tempSensor.requestTemperatures();  // Request temperature from sensor
    temperature = tempSensor.getTempCByIndex(0);  // Get the temperature (Celsius) from the first (and usually the only) sensor
    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.println(" °C");

    // === EC Sensor Readings ===
    int ecRaw = analogRead(A0);  // Read raw ADC value from EC pin
    Serial.print("EC Raw (ADC): ");
    Serial.println(ecRaw);

    // EC Voltage in mV
    float ecVoltage = voltage * 1000;  // Convert to mV
    Serial.print("EC Voltage (mV): ");
    Serial.println(ecVoltage, 4);

    // Convert voltage to EC value using temperature compensation
    ecValue = ec.readEC(voltage, temperature);  // EC in mS/cm
    Serial.print("EC (mS/cm): ");
    Serial.println(ecValue, 4);
  }

  ec.calibration(voltage, temperature); // Calibration via Serial CMD
}
