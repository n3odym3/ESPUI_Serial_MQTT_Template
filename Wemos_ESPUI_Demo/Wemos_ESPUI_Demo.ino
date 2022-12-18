/*
 This code has been made by Neodyme under the MIT license
 Youtube : https://www.youtube.com/neodymetv
 Twitch : https://www.twitch.tv/ioodyme
 Github : https://github.com/n3odym3
 ESPUI documentation : https://github.com/s00500/ESPUI#readme
*/

//Web server==================================
#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined ESP32
#include <WiFi.h>
#define LED_BUILTIN 2
#else
#error Architecture unrecognized by this code.
#endif

#include <Preferences.h>
Preferences preferences;
#include <DNSServer.h>
#define DNS_PORT 53
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
const char* hostname = "ESPUI-Demo";
bool wificonnected = false;
//Web server==================================

//MQTT=========================
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);
#define mqtt_retry_delay 10000
unsigned long last_millis = 0;
//MQTT=========================

//ESPUI=================================================================================================================
#include <ESPUI.h>
uint16_t wifi_ssid_text, wifi_pass_text;
uint16_t mqtt_server_text, mqtt_topic_in_text, mqtt_topic_out_text, mqtt_user_text, mqtt_pass_text, mqtt_enabled_switch;
uint16_t statusLabelId, serialLabelId;
String option;
String stored_ssid, stored_pass;
String stored_mqtt_server, stored_mqtt_user, stored_mqtt_pass, stored_mqtt_topic_in, stored_mqtt_topic_out;
bool mqtt_enabled = false;
//ESPUI==================================================================================================================

//Custom libraries..............
//Your code HERE !
//Custom libraries..............

//SETUP=========================
void setup() {

  //Custom setup...............
  //Your code HERE !
  //Custom setup...............

  Serial.begin(115200);
  Serial.println();
  //pinMode(LED_BUILTIN, OUTPUT);
  preferences.begin("Settings");
  wifi_init();
  espui_init();
}
//SETUP=========================

//LOOP==========================================
void loop() {
  dnsServer.processNextRequest();
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    ESPUI.print(serialLabelId, input);
    SerialSetup(input);
  }
  mqtt_loop();

  //Custom loop.................................
  //Your code HERE !
  //Custom loop.................................
}
//LOOP==========================================
