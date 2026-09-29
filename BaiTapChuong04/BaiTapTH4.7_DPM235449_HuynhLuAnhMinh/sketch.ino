#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// =========================
// PHẦN TX - MÁY PHÁT
// =========================

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Dữ liệu TX
float txTemperature = 0;
float txHumidity = 0;


// =========================
// PHẦN RX - MÁY THU
// =========================

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Dữ liệu RX nhận được
float rxTemperature = 0;
float rxHumidity = 0;


// =========================
// TX ĐỌC DỮ LIỆU
// =========================

void TX_ReadSensor() {

  txTemperature = dht.readTemperature();
  txHumidity = dht.readHumidity();

  if (isnan(txTemperature) || isnan(txHumidity)) {
    Serial.println("TX: LOI DHT22!");
    return;
  }

  Serial.println("========== TX ==========");

  Serial.print("TX Nhiet do: ");
  Serial.print(txTemperature, 1);
  Serial.println(" C");

  Serial.print("TX Do am: ");
  Serial.print(txHumidity, 1);
  Serial.println(" %");
}


// =========================
// TX TRUYỀN DỮ LIỆU
// =========================

void TX_SendData() {

  // Mô phỏng gói dữ liệu truyền đi
  String packet =
    "T:" + String(txTemperature, 1) +
    ",H:" + String(txHumidity, 1);

  Serial.print("TX Gui: ");
  Serial.println(packet);

  // =================================
  // MÔ PHỎNG KÊNH TRUYỀN
  // TX -> RX
  // =================================

  rxTemperature = txTemperature;
  rxHumidity = txHumidity;
}


// =========================
// RX NHẬN DỮ LIỆU
// =========================

void RX_ReceiveData() {

  Serial.println("========== RX ==========");

  Serial.print("RX Nhan nhiet do: ");
  Serial.print(rxTemperature, 1);
  Serial.println(" C");

  Serial.print("RX Nhan do am: ");
  Serial.print(rxHumidity, 1);
  Serial.println(" %");
}


// =========================
// RX HIỂN THỊ LCD
// =========================

void RX_DisplayLCD() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(rxTemperature, 1);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humi:");
  lcd.print(rxHumidity, 1);
  lcd.print(" %");
}


// =========================
// SETUP
// =========================

void setup() {

  Serial.begin(9600);

  // TX
  dht.begin();

  // RX
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MACH TX -> RX");

  lcd.setCursor(0, 1);
  lcd.print("Khoi dong...");

  delay(2000);
}


// =========================
// LOOP
// =========================

void loop() {

  // 1. TX đọc DHT22
  TX_ReadSensor();

  // 2. TX truyền dữ liệu
  TX_SendData();

  // 3. RX nhận dữ liệu
  RX_ReceiveData();

  // 4. RX hiển thị LCD
  RX_DisplayLCD();

  Serial.println();

  delay(2000);
}