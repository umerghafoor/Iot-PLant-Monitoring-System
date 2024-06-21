# IOT Plant Monitoring System

## Introduction

The IOT Plant Monitoring System is a project that aims to monitor the health and well-being of plants using Internet of Things (IoT) technology.

## components

This project consists of three main components:

1. **ESP32 Code**: Reads soil moisture data and sends it to a server.
2. **PHP Server Script**: Receives and stores soil moisture data in a MySQL database.
3. **Python GUI Application**: Fetches and displays the data from the database with smooth plots.

## Components and Their Functions

### 1. ESP32 Code (`main.ino`)

This code reads the soil moisture value from a sensor connected to the ESP32 and sends it to a server via an HTTP POST request.

#### Required Libraries

- WiFi.h
- HTTPClient.h

#### Setup Instructions

- Connect the soil moisture sensor to the specified pin (`soilMoisturePin = 32`).
- Update the WiFi credentials (`ssid` and `password`) and the server URL (`URL`).
- Upload the code to the ESP32.

#### Key Functions

- **connectWiFi()**: Connects the ESP32 to the WiFi network.
- **loop()**: Reads the soil moisture sensor value, calculates the moisture percentage, and sends the data to the server.

### 2. PHP Server Script (`test_data.php`)

This script receives the soil moisture data from the ESP32 and stores it in a MySQL database.
#### Setup Instructions

- Ensure you have a MySQL server running.
- Create a database named `soilmoisture_db` and a table named `dht11` with columns `Moisture`, `DateTime`, and `ID`.
- Update the database credentials (`hostname`, `username`, `password`, `database`) in the script.
- Deploy the script on a web server.

#### Key Functions

- Connects to the MySQL database.
- Inserts the received soil moisture data into the `dht11` table.

### 3. Python GUI Application (`main.py`)

This application fetches the last 25 and 500 entries from the database and displays them as smooth plots using Tkinter and Matplotlib.

#### Required Libraries

- mysql.connector
- tkinter
- ttk
- matplotlib
- scipy
- numpy

#### Setup Instructions

- Ensure you have Python and the required libraries installed.
- Update the MySQL database credentials (`db_config`).
- Run the script to start the GUI.

#### Key Functions

- **fetch_last_entries_and_show_smooth_plots()**: Fetches data from the database and updates the plots.
- **Tkinter GUI**: Displays the original data and plots in a blue-themed window.

---

## Complete Steps to Run the Project

1. **ESP32 Code**:
   - Connect the soil moisture sensor to the ESP32.
   - Update WiFi credentials and server URL in the code.
   - Upload the code to the ESP32.

2. **PHP Server Script**:
   - Set up a MySQL database and table.
   - Update the database credentials in the script.
   - Deploy the script on a web server.

3. **Python GUI Application**:
   - Install required libraries using `pip install mysql-connector-python tkinter matplotlib scipy numpy`.
   - Update the MySQL database credentials in the script.
   - Run the script using `python main.py`.

With these steps, your soil moisture monitoring system should be fully functional, allowing you to read, send, store, and visualize soil moisture data.
