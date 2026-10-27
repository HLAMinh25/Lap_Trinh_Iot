#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
#define LED_PIN 2

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (int i = 0; i < length; i++) msg += (char)payload[i];
  float temp = msg.toFloat();

  // Hiển thị Màn hình OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("WOKWI MQTT DEMO");
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print("t: "); display.print(temp, 1); display.println(" C");

  // Logic theo đề: >35C LED SÁNG, <35C LED TẮT
  display.setTextSize(1);
  display.setCursor(0, 48);
  if (temp > 35.0) {          // > 35°C -> Đèn sáng
    digitalWrite(LED_PIN, HIGH);
    display.println("LED: SANG (t > 35C)");
  } else {                    // < 35°C -> Đèn tắt
    digitalWrite(LED_PIN, LOW);
    display.println("LED: TAT (t < 35C)");
  }
  display.display();
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      String clientId = "WokwiSub-";
      clientId += String(random(0xffff), HEX);
      if (client.connect(clientId.c_str())) {
        client.subscribe("iot/lab/nhietdo");
      } else { delay(2000); }
    }
  }
  client.loop();
}