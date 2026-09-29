int buzzer = 8;
int LED = 7;
int flame_sensor = 4;
int flame_detected;

void setup() {
  // Khởi tạo giao tiếp Serial với máy tính ở tốc độ 9600 baud
  Serial.begin(9600);
  
  // Cấu hình các chân tín hiệu
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(flame_sensor, INPUT);
}

void loop() {
  // Đọc trạng thái từ cảm biến (hoặc công tắc mô phỏng)
  flame_detected = digitalRead(flame_sensor);
  
  if (flame_detected == 1) {
    // Nếu có tín hiệu mức CAO (phát hiện ngọn lửa)
    Serial.println("Phat hien ngon lua...!");
    digitalWrite(buzzer, HIGH);
    
    // Nháy đèn LED
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  } else {
    // Nếu tín hiệu mức THẤP (không có ngọn lửa)
    Serial.println("Khong co lua phat hien");
    digitalWrite(buzzer, LOW);
    digitalWrite(LED, LOW);
    
    // Đợi 1 giây trước khi đọc lại để tránh trôi chữ quá nhanh trên Serial
    delay(1000); 
  }
}