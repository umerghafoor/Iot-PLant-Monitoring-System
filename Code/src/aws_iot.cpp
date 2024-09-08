// aws_iot.cpp
#include "aws_iot.h"
#include "secrets.h"
#include "config.h"
#include <ArduinoJson.h>
#include <time.h>
#include <Arduino.h>

WiFiClientSecure net;
PubSubClient client(net);
time_t now;
struct tm timeinfo;

/**
 * The function `messageHandler` prints the received message topic and payload to the Serial monitor in
 * C++.
 * 
 * @param topic The `topic` parameter in the `messageHandler` function is a pointer to a character
 * array (string) that represents the topic of the message received. It is used to identify the
 * specific topic to which the message belongs.
 * @param payload The `payload` parameter in the `messageHandler` function is a pointer to a byte
 * array, which represents the data of the message that was received. It is of type `byte *` and is
 * used to access the content of the message.
 * @param length The `length` parameter in the `messageHandler` function represents the length of the
 * `payload` array, which is the number of bytes in the message payload that has been received. It
 * indicates the size of the data that needs to be processed or displayed.
 */
void messageHandler(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.write(payload, length);
    Serial.println();

    Serial.print("Raw message: ");
    Serial.write(payload, length);
    Serial.println();
}

/**
 * The function `connectAWS` establishes a connection to AWS IoT using MQTT protocol with necessary
 * certificates and subscribes to a specific topic.
 * CONSTANTS:
 * - AWS_CERT_CA: Amazon Root CA 1
 * - AWS_CERT_CRT: Device Certificate
 * - AWS_CERT_PRIVATE: Device Private Key
 * - AWS_IOT_ENDPOINT: AWS IoT endpoint
 * - AWS_IOT_SUBSCRIBE_TOPIC: Topic to subscribe to
 * - THINGNAME: Name of the IoT device
 */
void connectAWS() {
    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);

    client.setServer(AWS_IOT_ENDPOINT, 8883);
    client.setCallback(messageHandler);

    Serial.println("Connecting to AWS IoT");

    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect(THINGNAME)) {
            Serial.println("connected");
            if (client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC)) {
                Serial.println("Subscription successful");
            } else {
                Serial.println("Subscription failed");
            }
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

/**
 * The function `NTPConnect` sets the time using SNTP and prints the current local time after syncing
 * with an NTP server.
 */
void NTPConnect(void) {
    Serial.print("Setting time using SNTP");
    configTime(TIME_ZONE * 3600, 0, "pool.ntp.org", "time.nist.gov");

    now = time(nullptr);
    int retry = 0;
    const int maxRetries = 10;
    
    while (now < 24 * 3600 && retry < maxRetries) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
        retry++;
    }

    if (retry < maxRetries) {
        Serial.println("done!");
        localtime_r(&now, &timeinfo);
        Serial.print("Current local time: ");
        Serial.print(asctime(&timeinfo));
    } else {
        Serial.println("Failed to sync time with NTP server.");
    }
}


/**
 * The function `clientLoop` calls the `loop` function of the `client` object.
 */
void clientLoop() {
    client.loop();
}

/**
 * The function `publishMessage` creates a JSON document with humidity, temperature, soil moisture, and
 * timestamp data, then publishes it to an AWS IoT topic.
 * 
 * @param h The parameter `h` in the `publishMessage` function represents the humidity value that you
 * want to publish in the message. It is a floating-point number (float) indicating the humidity level.
 * @param t The parameter `t` in the `publishMessage` function represents the temperature value that
 * will be included in the JSON message to be published.
 * @param soilMoisture Soil moisture is a measure of the amount of water present in the soil. It is
 * typically expressed as a percentage representing the ratio of the volume of water in the soil to the
 * total volume of the soil. In the context of your code snippet, the `soilMoisture` parameter is
 */
void publishMessage(float h, float t, int soilMoisture) {
    // Update time before publishing
    now = time(nullptr);
    gmtime_r(&now, &timeinfo);

    // Create JSON document
    JsonDocument doc;
    doc["humidity"] = h;
    doc["temperature"] = t;
    doc["soilMoisture"] = soilMoisture;
    doc["timestamp"] = asctime(&timeinfo);

    // Debugging: Print data to serial
    Serial.print("Publish message: ");
    Serial.println(asctime(&timeinfo));

    Serial.print("Humidity: ");
    Serial.println(h);

    Serial.print("Temperature: ");
    Serial.println(t);

    Serial.print("Soil Moisture: ");
    Serial.println(soilMoisture);

    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);

    client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
