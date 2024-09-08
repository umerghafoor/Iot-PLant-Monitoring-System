#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"  // Include your AWS IoT credentials and WiFi credentials here
#include "DHT.h"

#define DHTPIN 14        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11    // DHT 11
#define SOIL_MOISTURE_PIN 34 // GPIO 34 (Analog pin)
#define AWS_IOT_PUBLISH_TOPIC   "Iot-PLant-Monitoring-System/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "Iot-PLant-Monitoring-System/sub"
#define TIME_ZONE 10  // Adjust this according to your timezone

float h;
float t;
int soilMoisturePercent;
time_t now;
struct tm timeinfo;

DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure net;
PubSubClient client(net);

void messageHandler(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.write(payload, length);
  Serial.println();

  // Print raw payload
  Serial.print("Raw message: ");
  Serial.write(payload, length);
  Serial.println();
}

/**
 * @brief Connects to Wi-Fi using WiFiManager library.
 */
void connectWifi()
{
  WiFiManager wm;
  Serial.print("Connecting to Wifi ");
  if (!wm.autoConnect())
  {
    Serial.println("Failed to connect, restarting...");
    delay(3000);
    ESP.restart();
  }
  Serial.println("Connected.");
}

/**
 * @brief Connects to the NTP server and sets the current time.
 */
void NTPConnect(void)
{
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, 0, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  while (now < 24 * 3600)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("done!");

  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}

/**
 * @brief Connects to the AWS IoT Core.
 */
void connectAWS()
{
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.setCallback(messageHandler);

  Serial.println("Connecting to AWS IoT");

  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(THINGNAME))
    {
      Serial.println("connected");
      if (client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC))
      {
        Serial.println("Subscription successful");
      }
      else
      {
        Serial.println("Subscription failed");
      }
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void publishMessage()
{
  // Read soil moisture
  int sensorValue = analogRead(SOIL_MOISTURE_PIN);
  soilMoisturePercent = map(sensorValue, 3550, 1200, 0, 100);

  // Create and serialize JSON document
  DynamicJsonDocument doc(200);
  doc["humidity"] = h;
  doc["temperature"] = t;
  doc["soilMoisture"] = sensorValue;
  doc["timestamp"] = asctime(&timeinfo);

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void setup()
{
  Serial.begin(115200);
  connectWifi();
  connectAWS();
  dht.begin();
  NTPConnect();
}

void loop()
{
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\tTemperature: ");
  Serial.print(t);
  Serial.println("°C");

  publishMessage();
  client.loop();
  delay(1000);
}
