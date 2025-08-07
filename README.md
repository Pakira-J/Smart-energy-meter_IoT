<h1 align="center">🔌 Smart Energy Meter with Remote IoT Monitoring</h1>



<p align="center">

&nbsp; <img src="Images/device\_real\_photo.jpg" width="300" alt="Smart Energy Meter Device" />

</p>



<p align="center">

&nbsp; <b>Built with ESP32 + PZEM-004T + Blynk</b>  

&nbsp; <br/>

&nbsp; <i>A solo-engineered embedded systems project for real-time power monitoring</i>

</p>



---



\## ⚡ Project Overview



The \*\*Smart Energy Meter\*\* is a compact embedded system that uses an \*\*ESP32 microcontroller\*\* and \*\*PZEM-004T multifunctional electric sensor\*\* to measure \*\*real-time voltage, current, power, and energy consumption\*\*. The data is pushed to the \*\*Blynk IoT platform\*\* for wireless remote monitoring via a mobile dashboard and web app.



> 🎯 This project was built entirely solo as part of my self-driven journey into Embedded Systems \& IoT.



---



\## 🧠 Tech Stack \& Components



| Category        | Tools/Hardware      |

|-----------------|---------------------|

| Microcontroller | ESP32 Wi-Fi Module  |

| Energy Sensor   | PZEM-004T (v3.0)    |

| IoT Platform    | Blynk (mobile app)  |

| IDE             | Arduino IDE         |

| Communication   | UART (Serial)       |

| Version Control | Git + GitHub        |



---



\## 🏗️ Features



\- 📈 Real-time measurement of voltage, current, power, and total energy used

\- 📲 Wireless data transmission to Blynk app

\- 💡 Mobile dashboard interface with live values

\- ⚙️ Modular and readable code

\- 🧠 Designed with scalability (e.g., relay control or cloud logging)



---



\## 🖼️ Project Media



<p float="left">

&nbsp; <img src="Images/device\_real\_photo.jpg" width="300" alt="Device Hardware"/>

&nbsp; <img src="Images/mobile\_app\_screenshot.jpg" width="300" alt="Blynk App Screenshot"/>

</p>



---



\## 🛠️ Circuit Schematic



<p align="center">

&nbsp; <img src="Schematics/circuit\_diagram.png" width="500" alt="Wiring Diagram" />

</p>



\*\*Wiring Summary:\*\*

\- 🟢 PZEM-004T → TX/RX to ESP32 UART2 (GPIO 16 \& 17 recommended)

\- 🔵 ESP32 → Powered by 5V

\- ⚫ Sensor → CT coil and mains voltage input as per spec

\- 📡 ESP32 connects to Wi-Fi and transmits data to Blynk cloud



---



<h1 align="center">⚡ Smart Energy Monitor using ESP32 + PZEM-004T + Blynk</h1>

<p align="center">

&nbsp; 🔌 Real-time Power Monitoring • 📲 Mobile Dashboard • ☁️ IoT Integration

</p>



---



\## 🚀 How It Works (Workflow)
<table>

&nbsp; <tr>

&nbsp;   <th>Step</th><th>Description</th>

&nbsp; </tr>

&nbsp; <tr>

&nbsp;   <td>🔌 ESP32 UART Setup</td>

&nbsp;   <td>Initializes UART communication with the PZEM-004T sensor.</td>

&nbsp; </tr>

&nbsp; <tr>

&nbsp;   <td>⚡ Sensor Reads Data</td>

&nbsp;   <td>Measures Voltage, Current, Power, and Energy from the connected load.</td>

&nbsp; </tr>

&nbsp; <tr>

&nbsp;   <td>📡 Wi-Fi Transmission</td>

&nbsp;   <td>ESP32 connects to Wi-Fi and transmits live data to the Blynk cloud server.</td>

&nbsp; </tr>

&nbsp; <tr>

&nbsp;   <td>📲 Mobile Dashboard</td>

&nbsp;   <td>Displays data in real time via the Blynk mobile application.</td>

&nbsp; </tr>

</table>



---



\## 🔒 Security \& Safety Notes



| ⚠️ Concern               | 🔍 Details                                                               |

|--------------------------|----------------------------------------------------------------------------|

| 🛡️ Authentication       | No user authentication – Blynk token is hardcoded.                         |

| ⚡ Mains Voltage Risk   | Not safe for direct mains usage without proper insulation \& isolation.    |

| 🎓 Usage Type           | Strictly for \*\*educational/demo\*\* purposes. Not production-grade.      |



---



\## 🧩 Future Improvements



| 💡 Feature               | 📌 Purpose                                                                |

|--------------------------|----------------------------------------------------------------------------|

| ☁️ Cloud Sync           | Integrate with Firebase, ThingSpeak, or MQTT for analytics \& remote access |

| 🔌 Remote Relay Control | Cut off power to load using Blynk app + Relay module                       |

| 📊 Data Logging         | Log data locally to SD card or sync to Google Sheets API                   |

| 📤 Offline Backup       | Add EEPROM or local storage fallback for Wi-Fi dropouts                    |



---



\## 🧠 What I Learned



| 🛠️ Area                   | 📘 Skills Gained                                                          |

|----------------------------|----------------------------------------------------------------------------|

| 🔧 Embedded Communication | UART protocol with energy meter (PZEM)                                     |

| ⚙️ Sensor Integration     | Real-time data handling, parsing, and calibration                          |

| 🌐 IoT Networking         | Blynk setup, Wi-Fi config, and mobile dashboard deployment                 |

| 🔗 GitHub Versioning      | Structured commits, branch management, and clean documentation             |

| 📝 Technical Writing      | Recruiter-ready README \& project explanations                             |



---



\## ⚙️ How to the run this project



\- 1. Clone the repo: git clone [https://github.com/yourusername/SmartEnergyMonitor.git](https://github.com/Pakira-J/Smart-energy-meter_IoT.git)

\- 2. Open firmware /in Arduino IDE

\- 3. Install official board manager for ESP32 by Espressif systems

\- 4. Install required libraries:
    	\- Blynk
    	\- LiquidCrystal_I2C
    	\- PZEM004T

\- 5. Configure your Wi-Fi SSID and Blynk Auth Token in the code

\- 6. Upload to ESP32

\- 7. Monitor power on your phone via the Blynk app



---



<p align="center"> <b>Built with 💻, 📱, and 🔌 by Joydeep Pakira</b> <br/> <a href="https://www.linkedin.com/in/pakira-joydeep/">🔗 Connect on LinkedIn</a> | <a href="mailto:pakira.joydeep@gmail.com">📧 Mail</a> </p> ```


---




\## 📂 Folder Structure



```bash

Smart-Energy-Meter-IoT/

├── smart\_energy\_meter/

│   └── smart\_energy\_meter.ino

├── Images/

│   ├── device\_real\_photo.jpg

│   └── mobile\_app\_screenshot.jpg

├── Schematics/

│   └── circuit\_diagram.pdf

├── README.md

└── LICENSE




