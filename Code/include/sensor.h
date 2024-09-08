#pragma once

#include <DHT.h>

// Variables for sensor data
extern float h;
extern float t;

// Function declarations for sensor initialization
void initSensor();

// Function declarations for sensor operations
float readSensorData_DHT_T();
float readSensorData_DHT_H();

// Function declarations for Soil Moisture Sensor
int readSensorData_SoilMoisture();