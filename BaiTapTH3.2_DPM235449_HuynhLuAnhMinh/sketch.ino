int sensorPin = A0;   // Chọn chân đầu vào cho biến trở
int ledPin = 13;      // Chọn chân cho LED (chân 13 trên bo mạch)
int sensorValue = 0;  // Biến để lưu trữ giá trị đọc từ cảm biến

void setup() {
  pinMode(ledPin, OUTPUT); // Khai báo ledPin là OUTPUT (ngõ ra)
}

void loop() {
  // Đọc giá trị từ biến trở (từ 0 đến 1023)
  sensorValue = analogRead(sensorPin);
  
  // Bật đèn LED
  digitalWrite(ledPin, HIGH);
  // Dừng chương trình theo thời gian tương ứng với giá trị biến trở (mili giây)
  delay(sensorValue);
  
  // Tắt đèn LED
  digitalWrite(ledPin, LOW);
  // Dừng chương trình theo thời gian tương ứng
  delay(sensorValue);
}