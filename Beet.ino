#include <Moisture32.h>

#include <WiFi.h>
#include <PubSubClient.h>

Moisture32 m1(12, 4095, 2100);
Moisture32 m2(27, 4095, 2100);
Moisture32 m3(33, 4095, 2100);

const char* ssid = "EVB-Seminar";
const char* password = "HgdHB&dP-S!";
const char* mqttServer = "raspberrypi.local";
const char* mqttUser = "your_MQTT_user"; // If MQTT broker requires authentication
const char* mqttPassword = "your_MQTT_password"; // If MQTT broker requires authentication
const int mqttPort = 1883;
const int beetNr = 5;


WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() { //Connect to a WiFi Network
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { //retry until you are connected
    delay(500);
    Serial.print(".");
  }

  Serial.println(""); 
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() { // reconnect to server in case  you get disconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

char* buildMsg(int nr, int s1, int s2, int s3) { //Build the String to send to the Server by converting all numbers to char arrays and adding them together
  char* msg = new char[13];
  char n1[3];
  char n2[3];
  char n3[3];
  char bNr[2];
  
  //convert integers to char Arrays
  itoa(nr, bNr, 10); 
  itoa(s1, n1, 10);
  itoa(s2, n2, 10);
  itoa(s3, n3, 10);
  
  //add all the char Arrays together
  strcpy(msg, bNr);
  strcat(msg, ",");
  strcat(msg, n1);
  strcat(msg, ",");
  strcat(msg, n2);
  strcat(msg, ",");
  strcat(msg, n3);
  
  
  return msg;
}


void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  
}

void loop() {
  if (!client.connected()) {
    delay(10000);
    reconnect();
  }

  client.publish("esp32/beet", buildMsg(beetNr, m1.getMoisture(12), m2.getMoisture(27), m3.getMoisture(33))); //Send message to Serverwith topic "esp32/beet"
  
  delay(5000); // Delay for 5 Minutes between each message
  
  client.loop();
}