# 🚗 Real-Time Vehicle Detection and Alert System for U-Bends

![Embedded Systems](https://img.shields.io/badge/Domain-Embedded%20Systems-blue)
![Microcontroller](https://img.shields.io/badge/MCU-ATmega328P-green)
![Wireless](https://img.shields.io/badge/Wireless-NRF24L01-orange)
![Simulation](https://img.shields.io/badge/Simulation-Proteus-purple)

---

## 📌 Project Overview

U-bends on roads—especially in hilly or mountainous areas—pose significant safety risks due to **limited visibility and sharp curves**. Drivers are often unable to see oncoming vehicles in time, leading to accidents and traffic congestion.

The **Real-Time Vehicle Detection and Alert System for U-Bends** is designed to **detect approaching vehicles from both directions** and provide **instant visual alerts** to drivers. By delivering real-time warnings, the system helps drivers take preventive actions, thereby improving road safety and traffic flow.

This project was developed as part of **EE6304 – Embedded System Design** at the  
**Department of Electrical and Information Engineering, Faculty of Engineering, University of Ruhuna, Sri Lanka**.

---

## 🎯 Objectives

- 🚦 Enhance road safety at blind U-bends  
- 👀 Improve driver awareness in low-visibility conditions  
- 🚚 Assist safe navigation for large vehicles (buses and trucks)  
- 🚗 Reduce traffic congestion and rear-end collisions  
- ⏱️ Provide fast and reliable real-time alerts  

---

## ⚙️ System Architecture

The system consists of **two identical units**, installed at **both ends of a U-bend**.

### 🔄 Working Principle

1. **Ultrasonic sensors** continuously measure the distance of approaching vehicles.
2. The **ATmega328P microcontroller** processes the distance data.
3. Detection information is transmitted wirelessly using **NRF24L01 transceiver modules**.
4. A **traffic-light-style LED system** provides visual alerts to drivers.

### 🚥 LED Indications

| LED Color | Meaning        |
|---------|----------------|
| 🔴 Red   | Stop           |
| 🟡 Yellow| Slow Down      |
| 🟢 Green | Go / Clear     |

---

## 🛠️ Hardware Components

- ATmega328P Microcontroller  
- HC-SR04 Ultrasonic Sensors  
- NRF24L01 Wireless Transceiver Modules  
- LED Indicators (Red, Yellow, Green)  
- Power Supply and Switching Circuit  

---

## 💻 Software & Tools

- **Atmel Studio** – Firmware development and compilation  
- **Proteus** – Circuit simulation and validation  

---

## 📡 Wireless Communication

Initially, Bluetooth modules were tested but later replaced due to:
- ❌ Limited communication range  
- ❌ Lack of reliable full-duplex communication  

The **NRF24L01** module was selected because it:
- ✅ Supports full-duplex communication  
- ✅ Provides longer and stable wireless range  
- ✅ Consumes low power  

---

## 🧠 Firmware Logic

- Continuous distance monitoring using ultrasonic sensors  
- Threshold-based decision making  
- Real-time wireless data transmission  
- Dynamic LED control based on vehicle position and movement  

The firmware logic was implemented using **flowchart-based control** and tested thoroughly in simulation.

---

## 🧪 Simulation & Testing

- Complete system simulated using **Proteus**
- Potentiometers used to emulate varying vehicle distances
- Wireless communication verified up to **60–70 meters**
- All functional scenarios validated before hardware implementation

---

## 📦 Final Prototype

The final system includes:
- Fully assembled and enclosed hardware modules  
- Wireless communication between both ends of the U-bend  
- Real-time LED-based alert mechanism  
- Manual power control switch  

The prototype demonstrated **reliable real-time vehicle detection and alerting** during testing.

---

## 📁 Repository Structure 

```text
├── code/
│   ├── transmitter/
│   └── receiver/
├── simulation/
│   └── proteus_files/
├── images/
│   └── final_product.jpg
├── report/
│   └── Group_02_Real-time_Vehicle_Detection_and_Alert_System.pdf
└── README.md
