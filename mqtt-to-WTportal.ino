/*
 Basic ESP8266 MQTT example
* currently no callback implemented
* you can change the device name inside MQTT msg.
* mqtt_server = "52.3.175.124";
* port = 1883;
* server credentials: "arun", "arun@home"
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "TP-LINK";       // use your WiFi router SSID
const char* password = "bappaditya";   // use your WiFi router password
const char* mqtt_server = "52.3.175.124";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //---------------- this part not implemented yet ---------------------------
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
  //------------------------------------------------------------------------------
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), "arun", "arun@home")) {
      Serial.println("connected");
      client.subscribe("inTopic");
    }
      
       else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 15000) {
    lastMsg = now;
    value = random(100);   //++value;
    snprintf (msg, 50, "{\"thingname\":\"xxxxxxxx\", \"a\": \"%d\"}", value);    // get a unique device tag from us
    //sprintf(G_dht_string, ",\"temperature\":%s,\"humidity\":%s", temp, hum) ;   // -> sample from other code
    //msg = "{\"thingname\":\"firstthing\", \"a\": \"36\"}"
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("thingtopic", msg);    // changed to thingtopic to send to our db, from outTopic
  }
}
