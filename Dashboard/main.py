import threading
from MQTT_Client import client
from dashboard import app, mqtt_data

# Append MQTT messages to the data list
def on_message(client, userdata, msg):
    global mqtt_data
    mqtt_data.append(float(msg.payload.decode()))
    mqtt_data = mqtt_data[-100:]  # Keep the last 100 messages

client.on_message = on_message

# Run the MQTT client loop in a separate thread
mqtt_thread = threading.Thread(target=client.loop_forever)
mqtt_thread.start()

# Run the Dash app
if __name__ == '__main__':
    app.run_server(debug=True)
