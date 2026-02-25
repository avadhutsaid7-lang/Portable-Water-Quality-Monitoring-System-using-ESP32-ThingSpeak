HARDWARE CONNECTIONS

--------------------DS18B20 TEMPERATURE SENSOR------------------

DATA → GPIO 5

--------------------TURBIDITY SENSOR----------------------------

A0 → GPIO35

--------------------pH SENSOR----------------------------

A0 → GPIO34

---------------------I2C LCD(16X2, Address 0x27)----------------------

SDA → GPIO 21

SCL → GPIO 22

----------------------BUZZER---------------------------------

+VE → GPIO 12

-VE → GND

DESCRIPTION
IoT Water Quality Monitoring System – ESP32
Overview

This project is an ESP32-based portable water quality monitoring system designed for real-time field analysis. It measures temperature, turbidity, and pH levels, displays data locally on an LCD, triggers alerts for abnormal conditions, and uploads readings to ThingSpeak for remote IoT monitoring.

Features

Real-time temperature measurement using DS18B20
Analog turbidity sensing
Analog pH measurement using BNC pH sensor module
16x2 I2C LCD live display
Threshold-based buzzer alert
WiFi connectivity
Cloud data logging using ThingSpeak
Periodic IoT updates using non-blocking timing logic

Hardware Components

ESP32
DS18B20 Temperature Sensor
Analog Turbidity Sensor
pH Sensor Module with BNC Probe
16x2 I2C LCD (0x27)
Active Buzzer
Rechargeable Power Source

System Working

The DS18B20 sensor measures water temperature using the OneWire protocol.
The turbidity sensor outputs an analog voltage corresponding to water clarity.
The pH sensor provides an analog voltage representing acidity/alkalinity.

The ESP32:

Reads all sensor values.

Displays temperature, pH, and turbidity on the LCD.

Activates the buzzer if temperature or pH exceeds predefined safe limits.

Uploads sensor data to ThingSpeak every 10 seconds for remote monitoring.

Communication Interfaces

OneWire Protocol (DS18B20)
Analog ADC Inputs (Turbidity & pH sensors)
I2C Communication (LCD)
WiFi (ThingSpeak Cloud Integration)

Key Learning Outcomes

IoT cloud integration using ThingSpeak
Sensor interfacing (analog and digital)
ADC handling on ESP32
Real-time embedded system design
Threshold-based alert logic implementation
Non-blocking timing using millis()

Author

Avadhut
