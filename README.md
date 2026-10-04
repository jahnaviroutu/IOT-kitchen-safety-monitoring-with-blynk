# IOT-kitchen-safety-monitoring-with-blynk
ESP32-based safety monitor that tracks gas levels, temperature, and humidity, sending real-time alerts and data to the cloud via Blynk. Upgraded from an Arduino-based version to add WiFi connectivity and remote monitoring.  Tech: ESP32 · DHT11 · MQ2 Gas Sensor · Blynk · Wokwi
# IoT Environmental Safety Monitor

An ESP32-based environmental safety monitoring system that tracks gas leaks, temperature, and humidity in real time, with live data sent to the cloud via **Blynk** for remote monitoring.

This project is an upgrade of an earlier Arduino UNO-based version, rebuilt on ESP32 to add WiFi connectivity and cloud-based alerts.

---## Screenshots

### Circuit Diagram
![Circuit Diagram](https://github.com/jahnaviroutu/IOT-kitchen-safety-monitoring-with-blynk/blob/2041874c8c8de1bfa189ee0276fd17b92b958e69/Screenshot%202026-10-04%20154425.png)

### Blynk Dashboard
![Blynk Dashboard](images/dashboard.png)

## Features

- 🔥 **Gas leak detection** using an MQ2 gas sensor
- 🌡️ **Temperature & humidity monitoring** using a DHT11 sensor
- 📶 **Real-time data transmission** over WiFi to the Blynk IoT platform
- 🚨 **Local alerts** via buzzer and LED when readings cross safe thresholds
- ☁️ **Remote dashboard** for live monitoring from anywhere

---

## Tech Stack

| Component      | Purpose                                                 |
|----------------|---------------------------------------------------------|
| ESP32          | Main microcontroller with built-in WiFi                 |
| MQ2 Gas Sensor | Detects LPG, smoke, and combustible gas leaks           |
| DHT11          | Measures temperature and humidity                       |
| Buzzer         | Local audible alert on threshold breach                 |
| LED            | Local visual alert on threshold breach                  |
| Blynk          | Cloud platform for remote data visualization and alerts |
| Wokwi          | Online simulator used to build and test the circuit     |

---

## How It Works

1. The MQ2 and DHT11 sensors continuously read gas concentration, temperature, and humidity levels.
2. The ESP32 processes these readings and checks them against safety thresholds.
3. If a reading crosses a threshold (e.g., gas leak detected, high temperature), the buzzer and LED trigger a local alert.
4. All sensor data is sent over WiFi to the Blynk app/dashboard, allowing the system to be monitored remotely in real time.

---

## Circuit Simulation

This project was built and tested on [Wokwi](https://wokwi.com/projects/476944125182564353), a browser-based simulator, before (or instead of) physical hardware deployment.

---

## Getting Started

### Requirements
- ESP32 board
- MQ2 gas sensor
- DHT11 sensor
- Buzzer
- LED
- Arduino IDE with ESP32 board support installed
- Blynk account and app

### Setup
1. Clone this repository.
2. Open the `.ino` file in Arduino IDE.
3. Install required libraries: `DHT sensor library`, `Blynk`.
4. Add your WiFi credentials and Blynk auth token in the code.
5. Upload the code to your ESP32.
6. Open the Blynk app/dashboard to view live readings.

---

## Future Improvements

- Add a PIR motion sensor for intrusion/occupancy detection
- Log historical data for trend analysis
- Add mobile push notifications for critical alerts

---

## Author

Built by Jahnavi Routu as part of an embedded systems project portfolio.
