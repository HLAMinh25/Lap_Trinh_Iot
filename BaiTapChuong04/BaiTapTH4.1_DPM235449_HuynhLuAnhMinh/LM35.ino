/*
  BÀI 4.1: MẠCH ĐO NHIỆT ĐỘ DÙNG LM35 + ARDUINO UNO + LCD 16x2
  ----------------------------------------------------------------
  Kết nối (đi qua breadboard, dùng thanh ray nguồn +/-):
  - LM35:  VCC -> ray + (5V) | GND -> ray - (GND) | OUT -> A1 (nối thẳng)
  - LCD:   RS->D12 | E->D11 | D4->D5 | D5->D4 | D6->D3 | D7->D2
           VSS->GND | VDD->5V | RW->GND
           V0 (contrast) -> chân giữa biến trở 10K
           A (backlight+) -> qua điện trở 220ohm -> 5V
           K (backlight-) -> GND
*/

#include <LiquidCrystal.h>

// Khai báo các chân LCD: RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Chân Vout của LM35 nối vào A1
const int lm35Pin = A1;

// Số lần đọc để lấy trung bình, giúp giảm nhiễu tín hiệu
const int soLanDoc = 10;

void setup() {
  lcd.begin(16, 2);            // LCD 16 cột, 2 hàng
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do:");
  Serial.begin(9600);
}

void loop() {
  // Đọc và lấy trung bình nhiều lần để giảm nhiễu (chống nhảy số)
  long tongReading = 0;
  for (int i = 0; i < soLanDoc; i++) {
    tongReading += analogRead(lm35Pin);
    delay(5);
  }
  int reading = tongReading / soLanDoc;

  // Arduino Uno: điện áp tham chiếu 5V, ADC 10-bit (0-1023)
  // LM35: 10mV / độ C  =>  nhiệt độ (C) = (reading * 5000.0 / 1024.0) / 10.0
  float voltage_mV = reading * (5000.0 / 1024.0);
  float temperatureC = voltage_mV / 10.0;

  // Hiển thị lên LCD, hàng thứ 2
  lcd.setCursor(0, 1);
  lcd.print(temperatureC, 1);   // in 1 số thập phân
  lcd.print((char)223);         // ký tự độ "°"
  lcd.print("C   ");            // khoảng trắng để xóa ký tự cũ nếu số ngắn hơn

  // In ra Serial Monitor để theo dõi/debug
  Serial.print("Nhiet do: ");
  Serial.print(temperatureC, 1);
  Serial.println(" C");

  delay(1000);  // cập nhật mỗi 1 giây
}
