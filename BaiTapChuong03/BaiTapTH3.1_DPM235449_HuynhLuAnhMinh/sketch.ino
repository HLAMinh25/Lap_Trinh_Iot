void setup() {
  // Khởi tạo giao tiếp Serial với tốc độ 9600 baud
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0); // Đọc giá trị điện áp tại chân A0 (từ 0 đến 1023)
  Serial.println(sensorValue);      // In giá trị đọc được ra Serial Monitor
  delay(1);                         // Tạo độ trễ nhỏ để ổn định giá trị
}