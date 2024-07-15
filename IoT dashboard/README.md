# Streamlit Application Setup Guide
Welcome to our Streamlit application! This guide will help you set up the application on your local machine using a virtual environment.
## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Clone the Repository](#clone-the-repository)
3. [Setting Up a Virtual Environment](#setting-up-a-virtual-environment)
4. [Installing Required Packages](#installing-required-packages)
5. [Running the Application](#running-the-application)
6. [Support](#support)

## Prerequisites
Make sure you have the following installed on your system:
- Python (version 3.7 or higher)
- Git

## Clone the Repository
First, clone the repository to your local machine using Git:
```bash
git clone https://github.com/KevinAndani/Air-pollution-monitoring-system-with-ESP32-anedya-iot-cloud.git
cd IoT Dashboard
```

## Setting Up a Virtual Environment
It's a good practice to use a virtual environment to manage dependencies. Follow these steps to set up a virtual environment:

### Windows
1. Open a command prompt in the project directory.
2. Create a virtual environment:
   ```bash
   python -m venv venv
   ```
3. Activate the virtual environment:
   ```bash
   venv\Scripts\activate
   ```

### macOS and Linux
1. Open a terminal in the project directory.
2. Create a virtual environment:
   ```bash
   python3 -m venv venv
   ```
3. Activate the virtual environment:
   ```bash
   source venv/bin/activate
   ```

## Installing Required Packages
Once the virtual environment is activated, install the required packages using the `requirements.txt` file:

```bash
pip install -r requirements.txt
```

## Running the Application
With the virtual environment activated and dependencies installed, you can now run the Streamlit application:

```bash
streamlit run New_Dashboard.py
```
## Support
If you encounter any issues or need further assistance, please open an issue in this repository or contact our support team.