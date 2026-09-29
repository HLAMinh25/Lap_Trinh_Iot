int redPin = 11;    // Chân nối với LED đỏ của LED RGB
int greenPin = 10;  // Chân nối với LED xanh lá của LED RGB
int bluePin = 9;    // Chân nối với LED xanh nước biển của LED RGB

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  setRgb(0, 0, 0);  // Đặt toàn bộ màu sắc ban đầu về 0
}

void loop() {
  int Rgb[3];       // Mảng chứa giá trị 3 chân RGB
  Rgb[0] = 255;     
  Rgb[1] = 0;
  Rgb[2] = 0;
  
  // Vòng lặp chuyển màu mượt mà
  for (int decrease = 0; decrease < 3; decrease += 1) {
    int increase = decrease == 2 ? 0 : decrease + 1;
    
    for (int i = 0; i < 255; i += 1) { 
      Rgb[decrease] -= 1;
      Rgb[increase] += 1;
      setRgb(Rgb[0], Rgb[1], Rgb[2]);
      delay(20);
    }
  }
}

void setRgb(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}