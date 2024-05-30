# ESP32 DHT11 Sensor with AWS IoT Core: Documentation and Setup Guide

This code provides a basic structure for connecting an ESP32 development board with a DHT11 sensor to AWS IoT Core for publishing temperature and humidity readings.  

## Components Used

* ESP32 Development Board
* DHT11 Sensor
* Breadboard and Jumper Wires
* WiFi Connection (SSID and Password)
* AWS Account (Free Tier Available)

## Software Required

* Arduino IDE ([https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE))
* ArduinoJson Library ([https://github.com/bblanchon/ArduinoJson](https://github.com/bblanchon/ArduinoJson))
* WiFiClientSecure Library (included in Arduino IDE)
* PubSubClient Library ([https://github.com/knolleary/pubsubclient/blob/master/src/PubSubClient.h](https://github.com/knolleary/pubsubclient/blob/master/src/PubSubClient.h))

## AWS IoT Core Setup

1. Create an AWS Account if you don't have one already.
2. Go to the AWS IoT Core service ([https://aws.amazon.com/iot/](https://aws.amazon.com/iot/)).
3. Create a "Thing" which represents your ESP32 device.
4. Download the certificate and private key files associated with the thing.
5. Note down the AWS IoT endpoint address.

## Code Explanation

### Libraries

* `DHT.h`: Provides functions to interact with the DHT sensor.
* `secrets.h` (**Replace with your actual file**): Stores sensitive information like WiFi credentials and AWS certificates (placeholders included in the provided code).
* `WiFiClientSecure.h`: Enables secure communication with AWS IoT Core using certificates.
* `PubSubClient.h`: Manages communication with the MQTT broker on AWS IoT Core.
* `ArduinoJson.h`: Enables working with JSON data format for sending sensor readings.
* `WiFi.h`: Provides WiFi connection functionalities.

### Constants

* `DHTPIN`: Defines the pin connected to the DHT sensor (change if using a different pin).
* `DHTTYPE`: Specifies the DHT sensor type (DHT11 in this case).
* `AWS_IOT_PUBLISH_TOPIC`: Topic used to publish sensor data to AWS IoT Core.
* `AWS_IOT_SUBSCRIBE_TOPIC` (**Optional**): Topic for subscribing to messages from AWS (not used in this example).

### Global Variables

* `h`: Stores humidity reading.
* `t`: Stores temperature reading.
* `dht`: Instance of the DHT library for interacting with the sensor.
* `net`: Instance of WiFiClientSecure for secure communication.
* `client`: Instance of PubSubClient for MQTT communication.

### Functions

* `connectAWS()`: Connects to the WiFi network and then to the AWS IoT Core endpoint using the provided credentials.
* `publishMessage()`: Creates a JSON document with sensor readings and publishes it to the defined topic on AWS IoT Core.
* `messageHandler()`: (**Optional**) Handles incoming messages on the subscribed topic (not used in this example).
* `setup()`: Initializes serial communication, connects to AWS, and starts the DHT sensor.
* `loop()`: Reads sensor data, checks for validity, publishes data to AWS, and loops with a delay.

### Setup Guide

1. Install the required libraries in the Arduino IDE. Library managers can be found under **Tools > Manage Libraries**.
2. In `secrets.h`, define the following constants replacing placeholders with your actual values:
    * `#define WIFI_SSID "your_wifi_ssid"`
    * `#define WIFI_PASSWORD "your_wifi_password"`
    * `#define THINGNAME "your_thing_name"` (replace with the name you created in AWS IoT Core)
    * Update the certificate definition strings (`AWS_CERT_CA`, `AWS_CERT_CRT`, and `AWS_CERT_PRIVATE`) by replacing the placeholder content with your downloaded certificates and private key. You can use online tools to convert the downloaded PEM files to a format suitable for the code (check online resources for specific methods).
3. Connect the DHT11 sensor to the ESP32 board according to the pin definition (`DHTPIN`) in the code.
4. Connect the ESP32 board to your computer using a USB cable.
5. In the Arduino IDE, select the appropriate board type for your ESP32
