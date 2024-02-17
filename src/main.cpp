#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);

  if (!bme.begin(0x76)) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1);
  }
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F; // Druck in hPa umrechnen

  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.print(F(" °C\tHumidity: "));
  Serial.print(humidity);
  Serial.print(F(" %\tPressure: "));
  Serial.print(pressure);
  Serial.println(F(" hPa"));

  delay(2000);
}
