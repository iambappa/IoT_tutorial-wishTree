#include <WiFiClientSecure.h>
//#include <ESP8266WiFi.h>    // needed for ESP8266 only
//#include <Arduino.h>

WiFiClientSecure client;
unsigned long shortSleeptime= 5e6;

unsigned long   wifiStart = 0 ;
unsigned long WIFI_CONNECT_TIMEOUT = 8000;
/*
const unsigned long AnalogIn  = 34; //34 for wishTree-ESP32;   // A0 for ESP8266, works in nodeMCU directly, Arduino needs voltage divider
int readingIn = 0;
unsigned long       Sleeptime = 15e6 ;  // 15 sec. deepsleep

const char* ssid = "TrackerAP";
const char* password = "1234567890";
*/
const char* host = "api.wisethingz.com";
const int httpsPort = 443;
//const char* deviceName = "wishTree5";

//void setup() {
  //Serial.begin(115200);
  
void ConnectToWiFi(const char* ssid, const char* password){
  
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);

  wifiStart = millis() ;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if(WIFI_CONNECT_TIMEOUT < (millis() - wifiStart)){
      esp_sleep_enable_timer_wakeup(shortSleeptime); // WIFI not found
      esp_deep_sleep_start();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use WiFiClientSecure class to create TLS connection
  
  Serial.print("connecting to ");
  Serial.println(host);

    if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
}

//void loop() {
  /*
  readingIn = analogRead(AnalogIn);
  Serial.println(readingIn);
  delay(200);

  String url = "/Dev/thingsapi?thingname=";
  url += deviceName;
  url += "&";
  url += "a";
  url += "=";
  url += readingIn;
  */

void request(String url){
  
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
  
  //Serial.println("Going to sleep");
  //ESP.deepSleep(Sleeptime);
}
