
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

Like for a regular Arduino code you can import libraries, define some global variables and put code in the *setup* and *main* functions.

**Avoid** using the *delay()* function in the loop ! The code should not be blocked for a long period of time as the ESPUI and MQTT functions needs to be called regularly. Instead, use the *millis()* function to create non blocking delays.

To subscribe to MQTT topics add the following line in the **reconnect()** function in *WiFiMQTT.ino*.

```
client.subscribe("demo_topic");
```

You can modify the **mqtt_callback()** function in *Callback.ino* to respond to MQTT commands. 

```
if(topic == "demo_topic"){
    client.publish("response_topic", "PONG")
    Serial.printl("Hello World")
}
``` 

You can add Serial commands by using the following template in the **SerialSetup()** function :

```
else if (input.indexOf("custom_cmd") > -1) {
   String demo_cmd = splitString(input, ' ', 1); //Get the command (String)
   Serial.println(demo_cmd); //Print the command
   preferences.putString("demo", "demo_cmd"); //Save the value in the Flash memory
 }
```

The GUI can be modified to add buttons, sliders, text input/output, tabs, ... (see [ESPUI documentation](https://github.com/s00500/ESPUI) by modifying the **espui_init()** function in *ESPUI.ino*

```
auto demo_tab = ESPUI.addControl(Tab, "", "demo");
auto demo_button = ESPUI.addControl(Button, "", "Button", None, demo_tab, textCallback);
```

Variables can be restored from the Flash memory by using the [Preferences library](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/preferences.html). Custom preferences can be added in the **wifi_init()** function in WiFiMQTT.ino.

```
int demo_last_reading = preferences.getInt("last_reading", 0);
```

## Serial commands

|Command|Value/function|Example|
|--|--|--|
| ssid | [text] | ssid mywifi |
| password | [text] | password mysecretpassword|
| mqtt | broker ip | mqtt 192.168.1.10 | 
| topicin | mqtt (subcribe) topic| topicin demo_in | 
| topicout | mqtt (publish) topic| topic demo_out | 
| mqtten | enable/disable MQTT| mqtten 1 or mqtten 0| 
| restart | [restart the ESP]| restart |
| info | [print all the settings] | info (will not print WiFi password) |
