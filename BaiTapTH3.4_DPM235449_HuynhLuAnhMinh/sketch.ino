const int kPinButton1 = 2; // Nút nhấn 1 (giảm độ sáng)
const int kPinButton2 = 3; // Nút nhấn 2 (tăng độ sáng)
const int kPinLed = 9;     // Chân PWM điều khiển LED

void setup() {
  pinMode(kPinButton1, INPUT);
  pinMode(kPinButton2, INPUT);
  pinMode(kPinLed, OUTPUT);
  
  digitalWrite(kPinButton1, HIGH); // Kích hoạt điện trở treo nội cho nút 1
  digitalWrite(kPinButton2, HIGH); // Kích hoạt điện trở treo nội cho nút 2
}

int ledBrightness = 128; // Đặt độ sáng ban đầu ở mức trung bình (50%)

void loop() {
  if (digitalRead(kPinButton1) == LOW) {
    ledBrightness--; // Bấm nút 1 thì giảm độ sáng
  }
  else if (digitalRead(kPinButton2) == LOW) {
    ledBrightness++; // Bấm nút 2 thì tăng độ sáng
  }

  // Giới hạn giá trị độ sáng luôn nằm trong khoảng từ 0 đến 255
  ledBrightness = constrain(ledBrightness, 0, 255);
  
  // Xuất tín hiệu PWM điều khiển độ sáng LED
  analogWrite(kPinLed, ledBrightness);
  
  delay(20); // Tạo độ trễ ổn định tín hiệu chống dội phím và mượt mắt
}