#include "DHT.h"

#define DHTPIN 2     // Chân SDA nối vào chân số 2 của Arduino UNO
#define DHTTYPE DHT22   // Loại cảm biến DHT 22 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Khoi dong cam bien thoi tiet DHT22...");
  dht.begin();
}

void loop() {
  delay(2000); // Đọc dữ liệu sau mỗi 2 giây

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Kiểm tra lỗi đọc dữ liệu
  if (isnan(h) || isnan(t)) {
    Serial.println("Loi: Khong the doc du lieu tu cam bien!");
    return;
  }

  Serial.print("Nhiet do: ");
  Serial.print(t);
  Serial.print(" °C | Do am: ");
  Serial.print(h);
  Serial.println(" %");
}