# Blind-U-Bend-Safety-System-Wireless-Vehicle-Detection-and-Alerting

🚗 Real-Time Vehicle Detection and Alert System for U-Bends
📌 Project Overview

U-bends on roads, especially in hilly or mountainous areas, pose a serious safety risk due to limited visibility and sharp curves. Drivers cannot clearly see oncoming vehicles, which often leads to accidents and traffic congestion.

This project proposes a Real-Time Vehicle Detection and Alert System for U-Bends, designed to detect approaching vehicles from both directions and provide instant visual alerts to drivers. By warning drivers in advance, the system helps reduce collisions and improves road safety.

This project was developed as part of EE6304 – Embedded System Design at the Department of Electrical and Information Engineering, Faculty of Engineering, University of Ruhuna, Sri Lanka.

🎯 Objectives

Enhance road safety at blind U-bends

Improve driver awareness in low-visibility conditions

Assist safe navigation for large vehicles (buses, trucks)

Reduce traffic congestion and rear-end collisions

Provide real-time, reliable vehicle alerts

🛠️ System Description

The system consists of two identical units, placed on either side of a U-bend.

Working Principle

Ultrasonic sensors continuously measure the distance of approaching vehicles.

Distance data is processed by an ATmega328P microcontroller.

Vehicle detection information is transmitted wirelessly using NRF24L01 transceiver modules.

Based on the detected vehicle position, a traffic-light-style LED system provides visual alerts:

🔴 Red – Stop

🟡 Yellow – Slow Down

🟢 Green – Go

This ensures both ends of the U-bend are informed in real time.

🔧 Hardware Components

ATmega328P Microcontroller

HC-SR04 Ultrasonic Sensors

NRF24L01 Wireless Transceiver Modules

LED Indicators (Red, Yellow, Green)

Power Supply & Switching Circuit

💻 Software & Tools

Atmel Studio – Firmware development and compilation

Proteus – Circuit simulation and testing

🔄 Communication Technology

Initially, Bluetooth modules were tested but were replaced due to:

Limited communication range

Lack of reliable full-duplex communication

The NRF24L01 module was selected because it:

Supports full-duplex communication

Offers longer and more reliable wireless range

Consumes low power

📊 System Logic (LED Indications)

Vehicle detected within critical distance → 🔴 Red ON

Vehicle approaching but not critical → 🟡 Yellow ON

No vehicle detected / safe distance → 🟢 Green ON

Vehicle leaving the U-bend → Gradual transition to Green

🧪 Simulation & Testing

The complete system was simulated using Proteus

Potentiometers were used to emulate different vehicle distances

Wireless communication was tested successfully up to 60–70 meters

Firmware logic was validated using flowchart-based decision control

📷 Final Product

The final prototype includes:

Fully assembled hardware modules

Wireless communication between both ends

Real-time LED-based warning system

Manual power control switch

The system demonstrated reliable real-time vehicle detection and alert functionality during testing.

📁 Repository Structure (Suggested)
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

👥 Team Members

EG/2020/3820

EG/2020/3823

EG/2020/3826

📚 References

ATmega328P Datasheet

nRF24L01+ Product Specification

If you want, I can also:

✨ Make this more eye-catching with emojis & badges

🧑‍💻 Rewrite it in a resume-friendly / recruiter-focused style

📌 Customize it for portfolio GitHub pinned repo

🖼️ Add image captions & demo GIF section

