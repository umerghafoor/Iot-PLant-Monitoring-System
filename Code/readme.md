# IoT Plant Monitoring System Code

This repository contains the code for an IoT-based plant monitoring system that connects to AWS IoT Core. The system collects and publishes sensor data (humidity, temperature, and soil moisture) to the cloud.

## Table of Contents

1. [Overview](#overview)
2. [File Structure](#file-structure)
3. [Configuration](#configuration)
   - [config.h](#configh)
   - [secrets.h](#secretsh)
4. [Setup Instructions](#setup-instructions)
5. [Functions](#functions)
   - [AWS IoT Functions](#aws-iot-functions)
   - [Sensor Functions](#sensor-functions)
6. [Troubleshooting](#troubleshooting)

## Overview

The system includes:

- **Wi-Fi Connection**: Uses `WiFiClientSecure` to connect to Wi-Fi.
- **AWS IoT Core**: Utilizes `PubSubClient` for MQTT communication with AWS IoT Core.
- **Time Synchronization**: Connects to NTP servers for accurate timekeeping.
- **Sensor Integration**: Reads data from a DHT11 sensor and a soil moisture sensor.

## File Structure

- **`aws_iot.h`**: Header file declaring functions for AWS IoT connectivity and message handling.
- **`secrets.h`**: Contains AWS IoT credentials, Wi-Fi credentials, and certificate information.
- **`config.h`**: Configuration file with pin definitions, MQTT topics, and time zone.
- **`sensor.h`**: Header file declaring functions for sensor initialization and data reading.
- **`main.cpp`**: Main source file utilizing the functions declared in the header files.

## Configuration

### `config.h`

- **DHTPIN**: Digital pin connected to the DHT sensor.
- **DHTTYPE**: Type of the DHT sensor (DHT11).
- **SOIL_MOISTURE_PIN**: GPIO pin connected to the soil moisture sensor.
- **AWS_IOT_PUBLISH_TOPIC**: MQTT topic for publishing sensor data.
- **AWS_IOT_SUBSCRIBE_TOPIC**: MQTT topic for subscribing to messages.
- **TIME_ZONE**: Adjust according to your timezone.

### `secrets.h`

- **WIFI_SSID**: Wi-Fi network SSID.
- **WIFI_PASSWORD**: Wi-Fi network password.
- **AWS_IOT_ENDPOINT**: Endpoint for AWS IoT Core.
- **AWS_CERT_CA**: Amazon Root CA certificate.
- **AWS_CERT_CRT**: Device certificate.
- **AWS_CERT_PRIVATE**: Device private key.

## Setup Instructions

1. **Install Libraries**: PlatformIO will handle library installation based on your `platformio.ini` configuration.
2. **Update Credentials**: Modify `secrets.h` with your AWS IoT and Wi-Fi credentials.
3. **Configure Time Zone**: Set the `TIME_ZONE` in `config.h`.
4. **Upload Code**: Use PlatformIO to upload `main.cpp` to your ESP32 board.

## Functions

### AWS IoT Functions

- **`connectAWS()`**: Connects to AWS IoT Core using MQTT.
- **`NTPConnect()`**: Synchronizes time with NTP servers.
- **`publishMessage(float h, float t, int soilMoisture)`**: Publishes sensor data to AWS IoT Core.
- **`clientLoop()`**: Keeps the MQTT client connected and processes messages.
- **`messageHandler(char *topic, byte *payload, unsigned int length)`**: Handles incoming MQTT messages.

### Sensor Functions

- **`initSensor()`**: Initializes the DHT11 sensor and soil moisture sensor.
- **`readSensorData_DHT_T()`**: Reads temperature from the DHT11 sensor.
- **`readSensorData_DHT_H()`**: Reads humidity from the DHT11 sensor.
- **`readSensorData_SoilMoisture()`**: Reads soil moisture level.

## Troubleshooting

- **Wi-Fi Connection**: Verify credentials and ensure good network coverage.
- **NTP Synchronization**: Check internet connectivity and NTP server availability.
- **AWS IoT Connectivity**: Confirm correct AWS IoT configuration, including endpoint, thing name, and credentials.

For additional help, refer to the [AWS IoT documentation](https://docs.aws.amazon.com/iot/latest/developerguide/what-is-iot.html) and [PlatformIO documentation](https://docs.platformio.org/en/latest/).
