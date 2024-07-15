# Pollution Monitoring System

This project is a pollution monitoring system that uses an ESP32 microcontroller to measure temperature, humidity, carbon monoxide (CO), and carbon dioxide (CO2) content in the air. The data is sent to the Anedya.io cloud platform for real-time visualization. The system also includes an email alert feature for threshold breaches and a Python-based dashboard using Streamlit for data visualization and analysis.

## Features

- **Real-time Data Measurement:** Measures temperature, humidity, CO, and CO2 levels using sensors connected to the ESP32.
- **Cloud Integration:** Sends the measured data to the Anedya.io cloud platform for real-time visualization.
- **Email Alerts:** Sends email alerts to the user when any metric crosses predefined thresholds.
- **Streamlit Dashboard:** Provides a web-based dashboard for users to log in, view data, and plot graphs based on user-defined time ranges.
- **Data Storage:** Stores the fetched real-time data in a CSV file on the user's computer for data security and further analysis.

## Components

- **ESP32 Microcontroller**
- **Temperature and Humidity Sensor**
- **CO and CO2 Sensors**
- **Anedya.io Cloud Platform**
- **Email Service (SMTP)**
- **Streamlit Web Application**

## Setup Instructions
- **Clarity:** Emphasize at the beginning of this section that detailed setup instructions are provided within the codebase folders themselves.
- **Directory Structure:** Briefly explain the overall structure of your project's directories. Mention any important folders users should be aware of.
- **Example:** Optionally, provide a concise example of how to navigate to a specific folder and follow the instructions within.