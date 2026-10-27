#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

// Wifi giả lập mặc định của Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMsg = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      String clientId = "WokwiPub-";
      clientId += String(random(0xffff), HEX);
      if (!client.connect(clientId.c_str())) { delay(2000); }
    }
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    float temp = dht.readTemperature();
    if (!isnan(temp)) {
      char tempStr[8];
      dtostrf(temp, 1, 2, tempStr);
      client.publish("iot/lab/nhietdo", tempStr);
      Serial.print("Wokwi Node 1 -> Gui Temp: ");
      Serial.println(tempStr);
    }
  }
}