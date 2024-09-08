#pragma once

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Function declarations for AWS IoT
void connectAWS();
void NTPConnect();

void clientLoop();
void messageHandler(char *topic, byte *payload, unsigned int length);
void publishMessage(float h, float t, int soilMoisture);
