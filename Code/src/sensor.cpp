// sensor.cpp
#include "sensor.h"
#include "config.h"
#include <Arduino.h>

DHT dht(DHTPIN, DHTTYPE);
float h;
float t;

/**
 * The function `initSensor()` initializes a sensor for measuring temperature and humidity.
 */
void initSensor() {
    dht.begin();
}

/**
 * The function `readSensorData_DHT_T` reads temperature data from a DHT sensor and returns the
 * temperature value.
 * 
 * @return The function `readSensorData_DHT_T` is returning the temperature read from the DHT sensor.
 */
float readSensorData_DHT_T() {
    if (isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
    }
    return dht.readTemperature();
}

/**
 * The function reads humidity sensor data from a DHT sensor and prints an error message if the data is
 * invalid.
 * 
 * @return The function `readSensorData_DHT_H()` is returning the humidity value read from the DHT
 * sensor using the `dht.readHumidity()` function.
 */
float readSensorData_DHT_H() {
    if (isnan(h)) {
        Serial.println("Failed to read from DHT sensor!");
    }
    return dht.readHumidity();
}

/**
 * The function `readSensorData_SoilMoisture` reads the soil moisture data from a sensor connected to a
 * specific pin.
 * 
 * @return The function `readSensorData_SoilMoisture()` is returning the analog reading from the pin
 * specified by `SOIL_MOISTURE_PIN`.
 */
int readSensorData_SoilMoisture() {
    return analogRead(SOIL_MOISTURE_PIN);
}