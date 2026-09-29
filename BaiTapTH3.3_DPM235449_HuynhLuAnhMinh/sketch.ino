const int kPinButton1 = 2; // Chân nối với nút nhấn
const int kPinLed = 9;     // Chân nối với LED

void setup() {
  pinMode(kPinButton1, INPUT);           // Cài đặt chân nút nhấn là INPUT
  digitalWrite(kPinButton1, HIGH);       // Kích hoạt điện trở treo nội (Pull-up) bên trong Arduino
  pinMode(kPinLed, OUTPUT);              // Cài đặt chân LED là OUTPUT
}

void loop() {
  // Vì dùng điện trở treo, khi nhấn nút, chân D2 sẽ nhận mức tín hiệu LOW
  if (digitalRead(kPinButton1) == LOW) {
    digitalWrite(kPinLed, HIGH);         // Bật đèn LED sáng
  } else {
    digitalWrite(kPinLed, LOW);          // Tắt đèn LED
  }
}