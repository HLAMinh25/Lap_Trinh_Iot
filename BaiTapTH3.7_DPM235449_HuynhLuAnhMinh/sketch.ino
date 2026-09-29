#include <PololuLedStrip.h>

// Tạo một đối tượng ledStrip và chỉ định chân số 12 mà đối tượng sử dụng
PololuLedStrip<12> ledStrip;

// Định nghĩa số lượng LED trên dải (ví dụ: 32 LED)
#define LED_COUNT 32

// Tạo một bộ đệm để chứa các màu sắc (mỗi màu cần 3 byte cho R, G, B)
rgb_color colors[LED_COUNT];

void setup() {
  // Không cần cấu hình gì thêm trong setup đối với thư viện này
}

// Hàm chuyển đổi màu sắc từ hệ màu HSV sang RGB
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - (f * (uint16_t)s / 255)) * (uint16_t)v / 255;
  uint8_t t = (255 - ((255 - f) * (uint16_t)s / 255)) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  
  switch((h / 60) % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }
  
  return rgb_color(r, g, b);
}

void loop() {
  // Cập nhật các màu sắc dựa trên thời gian thực millis()
  uint16_t time = millis() >> 2;
  
  for (uint16_t i = 0; i < LED_COUNT; i++) {
    byte x = (time >> 2) - (i << 3);
    // Tính toán màu sắc cầu vồng theo hệ HSV
    colors[i] = hsvToRgb((uint32_t)x * 359 / 256, 255, 255);
  }
  
  // Ghi mảng màu sắc xuống dải LED RGB
  ledStrip.write(colors, LED_COUNT);
  
  delay(10); // Độ trễ nhỏ để ổn định khung hình hiệu ứng
}