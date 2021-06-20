/* Code for ESP32, by Bappaditya"*/

#include "header.h"

const unsigned long AnalogIn  = 34; //34 for wishTree-ESP32;   // A0 for ESP8266, works in nodeMCU directly, Arduino needs voltage divider
int readingIn = 0;
float randFloat;
String Status = "Closed";
int Run ;
float LAT;
float LONG;

unsigned long       Sleeptime = 15e6 ;  // 15 sec. deepsleep

const char* id = "TP-LINK";   // use you WiFi router SSID; removed "const" specifier- otherwise not compiling -> then added "const" in .h and .cpp -> then worked
const char* pw = "bappaditya";   // use your router password

const char* deviceName = "xxxxxx";    // get a valid device tag from us

void setup() {
  Serial.begin(115200);
  ConnectToWiFi(id, pw);
  esp_sleep_enable_timer_wakeup(Sleeptime);   // needed for ESP32 only
}

void loop() {
  Serial.println("-------------------------------------------------");
  Serial.print("Device name: ");
  Serial.println(deviceName);

  readingIn = analogRead(AnalogIn);
  Serial.println("Battery reading: " + String(readingIn));
  delay(200);
  randFloat = random(100)/1.0f;  // generate a random number from 0 to 199
  Serial.println("Random: " + String(randFloat));
  Run = random(2);
  if (Run%2 == 0){
  Status = "Closed";}
  else
  {Status = "Open";}
  Serial.println("Door Status: " + Status);
  LAT = random(1900, 2100) / 100.00f;
  LONG = random(7300, 7500) / 100.00f;
  Serial.print("LAT n LONG: ");
  Serial.print(LAT);
  Serial.print(" / ");
  Serial.println(LONG);
  Serial.println("----------------------------------------------------");

  String Url = "/Dev/thingsapi?thingname=";  Url += deviceName;
  Url += "&";
  Url += "analog";  Url += "=";   Url += readingIn;
  Url += "&";
  Url += "random";  Url += "=";   Url += randFloat;
  Url += "&";
  Url += "status";  Url += "=";   Url += Status;
  Url += "&";
  Url += "Lat";   Url += "=";   Url += LAT;
  Url += "&";
  Url += "Long";  Url += "=";   Url += LONG;

  request(Url);
  
  Serial.println("Going to sleep");
  //ESP.deepSleep(Sleeptime);   // for ESP8266 sleep
  esp_deep_sleep_start();       // for ESP32 sleep
}
