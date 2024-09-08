# IoT Plant Monitoring System

## Project Overview

The IoT Plant Monitoring System is a smart system designed to monitor plant health using sensors and send data to the cloud for analysis. It integrates with AWS IoT Core to provide real-time updates on plant conditions, including humidity, temperature, and soil moisture levels.

## Features

- **Real-Time Monitoring**: Tracks plant conditions and provides updates via AWS IoT Core.
- **Data Publishing**: Sends sensor data to AWS IoT Core for remote monitoring and analysis.
- **Time Synchronization**: Ensures accurate timestamps using NTP servers.
- **Wi-Fi Connectivity**: Connects to Wi-Fi using ESP32 and saves Wi-Fi credentials.

## Components

- **DHT11 Sensor**: Measures ambient humidity and temperature.
- **Soil Moisture Sensor (Capacitive)**: Measures soil moisture content.
- **ESP32 Dev Board**: Handles sensor data collection and communication with AWS IoT Core.
- **AWS IoT Core**: Manages data communication and storage in the cloud.

## Getting Started

1. **Hardware Setup**:
   - Connect the DHT11 sensor and soil moisture sensor to the ESP32 according to the pin configuration specified in `config.h`.

2. **Software Setup**:
   - Install the necessary libraries: `WiFiClientSecure`, `PubSubClient`, `ArduinoJson`, and `DHT`. You can also use PlatformIO to manage dependencies.
   - Update the `secrets.h` file with your AWS IoT credentials (endpoint, thing name, private key, certificate) and Wi-Fi details (SSID, password).
   - Set the appropriate time zone in `config.h` to ensure accurate timestamps.
   - Upload the code to your ESP32 board using the Arduino IDE or PlatformIO.

## Usage

1. **Setup AWS IoT Core**:
   - Configure your AWS IoT Core settings to create an IoT thing and obtain necessary credentials (endpoint, thing name, private key, certificate).

2. **Configure `secrets.h`**:
   - Enter your AWS IoT credentials and Wi-Fi details in the `secrets.h` file.

3. **Connect to ESP32**:
   - Ensure that the ESP32 is powered and connected to the same Wi-Fi network specified in `secrets.h`.

4. **Monitor Data**:
   - Access the sensor data via AWS IoT Core. You can also integrate with other cloud-based data analysis tools for further insights.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- AWS IoT Core
- Arduino Community
- Libraries and Tools used in development

## Contact

For questions or feedback, please contact Umer Ghafoor at <umerghaforr@gmail.com>.
