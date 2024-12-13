import paho.mqtt.client as mqtt

# AWS IoT Core endpoint
endpoint = "a3aap03cjx0go8-ats.iot.us-east-1.amazonaws.com"
cert_path = "AWS data/Device Certificate.crt"
key_path = "AWS data/Private Key.key"
ca_path = "AWS data/AmazonRootCA1.pem"

AWS_IOT_PUBLISH_TOPIC = "Iot-PLant-Monitoring-System/pub"

# Define the MQTT client
client = mqtt.Client(protocol=mqtt.MQTTv5)

# Configure TLS
client.tls_set(ca_path, certfile=cert_path, keyfile=key_path)

# Callback when the client connects to the broker
def on_connect(client, userdata, flags, reason_code, properties):
    # print(f"User data: {userdata}")
    # print(f"Flags: {flags}")
    # print(f"Reason code: {reason_code}")
    # print(f"Properties: {properties}")

    if reason_code == 0:
        print(f"Connected to AWS IoT Core with result code {reason_code}")
        client.subscribe(AWS_IOT_PUBLISH_TOPIC)
        print(f"Subscribed to topic: {AWS_IOT_PUBLISH_TOPIC}")
    else:
        print(f"Failed to connect to AWS IoT Core with result code {reason_code}")

# Callback when a message is received
def on_message(client, userdata, msg):
    print(f"Received message: {msg.payload.decode()}")

# Callback when subscription is confirmed by AWS IoT Core
def on_subscribe(client, userdata, mid, granted_qos):
    print(f"Subscribed to topic with QoS: {granted_qos}")

# Callback for when an error occurs
def on_error(client, userdata, msg):
    print(f"Error: {msg}")

client.on_connect = on_connect
client.on_message = on_message
client.on_subscribe = on_subscribe
client.on_log = on_error  # Add this line for error logging

try:
    # Connect to AWS IoT Core
    client.connect(endpoint, 8883, 60)

    print("Connected!")

    # Start the MQTT client loop
    client.loop_forever()

    print("Loop exited unexpectedly")

except Exception as e:
    print(f"An error occurred: {e}")
    client.disconnect()
