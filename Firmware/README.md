# Arduino IDE Setup Guide
This guide will walk you through setting up the Arduino IDE for our project, including installing necessary libraries, configuring variables, and providing instructions for manual installation if the Arduino IDE is not already installed.

## Prerequisites
**Arduino IDE**: Ensure that you have the Arduino IDE installed on your computer. If not, follow the instructions below to install it.

## Step 1: Installing Arduino IDE
### Windows
1. Download the Arduino IDE from the official website: [Arduino IDE Download](https://www.arduino.cc/en/software).
2. Run the installer and follow the on-screen instructions.

### macOS
1. Download the Arduino IDE from the official website: [Arduino IDE Download](https://www.arduino.cc/en/software).
2. Open the downloaded file and drag the Arduino application to your Applications folder.

### Linux
1. Download the Arduino IDE from the official website: [Arduino IDE Download](https://www.arduino.cc/en/software).
2. Extract the downloaded file.
3. Open a terminal and navigate to the extracted folder.
4. Run the installation script:
   ```bash
   sudo ./install.sh
   ```

## Step 2: Installing Required Libraries
Open the Arduino IDE and follow these steps to install the necessary libraries:

> [!NOTE] Install ESP32 Board
> If you don't have installed ESP32 Board then download it by following steps:
[Installing ESP32](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/#:~:text=Installing%20ESP32%20Add%2Don%20in%20Arduino%20IDE)

### Download the required libraries: 
1. Go to `Sketch` > `Include Library` > `Manage Libraries...`.
2. In the Library Manager, search for and install the following libraries:
   - **ArduinoJson** *by Benoit Blanchon...*: Simple and efficient library for the embedded C++.
   - **DHT sensor library** *by Adafruit*: For DHT sensor support (temperature and humidity).
   - **WiFi**: For managing Wi-Fi connections.
   - **WiFiClientSecure** *[by hugethor](https://github.com/hugethor/WiFiClientSecure)*: Secure conection using TLS (SSL).
   - **PubSubClient** *by Nick O'Leary*: A client library for the MQTT messaging.
   - **Time** *by Michael Margolis*: For real-time date and time functions. 
   - **ESP Mail Client** *by Mobizt*: For send, read and get mail. 

## Step 3: Configuring Variables
Before uploading the code to your board, you need to replace certain variables with your specific details. Open the main sketch file (`.ino` file) and locate the following variables:

> [!Attention]+  make the `anedya.h` file in the Firmware folder
> `#ifndef ANEDYA_H`
> `#define ANEDYA_H`
> `extern const char *deviceID = "Your_deviceID";`
> `extern const cjhar *connectionkey = "Your_connectionkey";`
> `#endif`

1. **Wi-Fi SSID**: Replace `WIFI_SSID` with your Wi-Fi network name (SSID) in the `x_wifi.ino` file.
   ```cpp
   const char* ssid = "your_wifi_ssid";
   ```

2. **Wi-Fi Password**: Replace `WIFI_PASSWORD` with your Wi-Fi network password in the `x_wifi.ino"` file.
   ```cpp
   const char* password = "your_wifi_password";
   ```

## Step 4: Connect sensors
Read `dht_sensor.h` for connecting the DHT11/22 sensor and read the main sketch carefully to connecting the other sensors .
## Step 5: Uploading the Code
1. Connect your Arduino/ESP32 board to your computer via USB.
2. Open the Arduino IDE.
3. Select the appropriate board and port:
   - Go to `Tools` > `Board` and select your board (e.g., `ESP32 Dev Module` for ESP32).
   - Go to `Tools` > `Port` and select the correct port (e.g., `COM3` or `/dev/ttyUSB0`).
4. Click the `Upload` button (right arrow icon) to compile and upload the code to your board.

## Troubleshooting
- If you encounter any issues with library installations, ensure that your Arduino IDE is up to date.
- Verify your board and port settings if the code fails to upload.

## Support
If you need further assistance, please refer to the [Arduino Official Documentation](https://www.arduino.cc/en/Guide) or contact our support team.