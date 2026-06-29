# 👶🍼 SMART BABY CARE SYSTEM

![HTML5](https://img.shields.io/badge/html5-%23E34F26.svg?style=for-the-badge&logo=html5&logoColor=white)
![Machine Learning](https://img.shields.io/badge/Machine%20Learning-Hugging%20Face-orange)
![Firebase](https://img.shields.io/badge/firebase-%23039BE5.svg?style=for-the-badge&logo=firebase)
![LabVIEW](https://img.shields.io/badge/LabVIEW-National%20Instruments-blue)

Welcome to the frontend repository of the **Smart Baby Care System**. This project was developed as the main hardware project for the **EE2044 - Electrical Measurements and Instrumentation** module at the Department of Electrical Engineering, University of Moratuwa.

🌐 **Live Dashboard:** [Click here to view the Web App](https://senuja-dilmith.github.io/SMART-BABY-CARE-SYSTEM/)
🌐 **Visit on LinkedIn:** [Click here](https://www.linkedin.com/posts/senuja-dilmith-745825349_engineering-iot-labview-ugcPost-7477016079890923520-kYB9/)

## 📖 About This Repository
This repository hosts the pure **HTML-based** User Interface (UI) for our IoT-enabled automated cradle system. 

## 📸 Our Team And Product
<img src="2d0e1865-d904-4030-9448-aa4d2e692ab3.jpg" width="300" alt="Our Teeam">

<img src="12c5061b-0717-4c70-92f8-5e95d32a2154.jpg" width="300" alt="Our Product">


## 🧠 The Machine Learning Pipeline (Baby Detection)
One of the core innovations of this project is the integration of a Machine Learning module to ensure 100% accurate crying detection and baby safety.
* **Image Capture:** An **ESP32-CAM** module is mounted on the cradle, programmed to capture a live photo every 10 seconds.
* **ML Inference:** These images are sent to a pre-trained ML model hosted on **Hugging Face** to detect whether the baby is present in the crib or not.
* **Cloud Sync & Logic:** The ML prediction is updated in **Firebase**. Our main LabVIEW system reads this data and combines it with the Sound Sensor data using an `AND` logic operation. 

## ✨ Key Features of the Dashboard
The dashboard allows parents to monitor and control the smart cradle remotely:
* **Live Environment Monitoring:** View real-time room temperature and light levels (Lux).
* **Smart Alerts & Status:** Receive instant updates on Baby's presence, Crying alerts, Bed wet status, and Cradle movement.
* **Remote Actuator Control:** Toggle the room cooling fan and deploy/reset the automated mosquito net.

## 🛠️ The Complete System Tech Stack
* **Frontend:** HTML (Hosted on GitHub Pages)
* **Backend & Cloud:** Firebase Realtime Database
* **Machine Learning:** Hugging Face API, ESP32-CAM
* **Core Logic & Controllers:** NI DAQ Card, Arduino, LabVIEW
* **Custom Hardware:** Custom-calibrated Angle sensor, Lux level sensor, Sound Sensor, Wet Sensor, Temperature Sensor.

## 👥 Meet the Team
* **Senuja Dilmith**
* **Kisal Dias**
* **Mahimi colombavidanage**

---
*Built with ❤️ for EE2044 | University of Moratuwa, Sri Lanka*
