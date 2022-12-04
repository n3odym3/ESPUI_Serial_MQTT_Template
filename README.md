# ESPUI Serial MQTT Template

## What is the purpose of this code ?

Building a new ESP project from scratch can be time-consuming and complex for beginners, this template allows you to kickstart your project by providing some useful tools such as :

- **Saving variables in the flash memory** to keep them in memory even if the ESP is restarted
- **Bidirectional serial communication**
- **WiFi connection** (SSID and password are saved in the flash memory and can be changed via serial command without needing to recompile the code)
- **Web GUI** to control the ESP or remotely visualize sensors values.
- **Access point creation** if the WiFi is unavailable or the setup the WiFi SSID and password.
- **MQTT** 

By design, this code alone is "useless", it's a **template** that is designed to be modified by adding your code in the ```//Your code HERE !``` sections.

## What does the code do ?

When the ESP is powered ON, it will :

- Load the settings stored in the flash memory (SSID, password, MQTT server, MQTT topic, custom variables)
- Try to connect to the last saved WiFi
- Create a Graphical User Interface 
- Respond to serial commands (ssid xxx, password xxx, mqtt xxx, mqtten xxx, ...)
- If the ESP **is** connected to the WiFi 
	- Print the IP of the ESP (you can access the web GUI from this IP)
	- Connect to the MQTT broker (if MQTT is enabled)
	- Run the code in the loop function
- If the ESP **is not** connected to the WiFi 
	- Create an access point (you can connect you smartphone to the acces point to have access to the GUI at **192.168.4.1**)
	- Run the code in the loop fonction

## Dependencies 

 - [ArduinoJSON 6.x](https://github.com/bblanchon/ArduinoJson)
 - [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) (for ESP32)
 - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
 - [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP) (for ESP8266)
 - [ESPUI](https://github.com/s00500/ESPUI)
 - [LittleFS](https://github.com/lorol/LITTLEFS)
 - [Preferences](https://github.com/vshymanskyy/Preferences) (for ESP8266)
 - [PubSubClient](https://github.com/knolleary/pubsubclient)

## Usage
