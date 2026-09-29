// ldr.chip.c - Quang trở LDR + chiết áp 10K tạo thành cầu phân áp (như sơ đồ sách)
//
//   +5V ---[ LDR ]---+--- OUT (nối vào base Q1)
//                    |
//                 [ POT 10K ]
//                    |
//                   GND
//
// Wokwi không có LDR rời và không giải được mạch phân áp analog, nên chip này tự tính
// điện áp của cầu phân áp rồi xuất ra chân OUT ở dạng số:
//   Vb = 5V * Rpot / (Rldr + Rpot)
//   OUT = CAO khi Vb >= 0.65V (đủ để mở Q1), THẤP khi Vb < 0.60V.
//
// Chân:
//   LIGHT : nối vào chân SIG của 1 chiết áp Wokwi = "cường độ ánh sáng" (0..5V = tối..rất sáng)
//   POT   : nối vào chân SIG của chiết áp 10K trong sách (chỉnh độ nhạy)
//   OUT   : nối vào base của Q1
//   VCC, GND: chỉ để nối dây cho giống sơ đồ (chip mặc định VCC = 5V)

#include "wokwi-api.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define VCC_VOLT   5.0f      // điện áp cấp (điện áp tham chiếu ADC của Wokwi cũng là 5V)
#define R_POT_MAX  10000.0f  // chiết áp 10K
#define VBE_ON     0.65f     // ngưỡng bật Q1
#define VBE_OFF    0.60f     // ngưỡng tắt Q1 (trễ nhỏ để không nhấp nháy)

// Điện trở LDR (Ohm) theo mức sáng, 9 mốc từ tối -> sáng
// (khoảng 1, 3, 10, 30, 100, 300, 1000, 3000, 10000 lux, kiểu LDR nhỏ thông thường)
#define TABLE_SIZE 9
static const float LDR_OHM[TABLE_SIZE] = {
  250600.0f, 111900.0f, 50000.0f, 22300.0f, 9980.0f, 4460.0f, 1990.0f, 889.0f, 397.0f
};

typedef struct {
  pin_t pin_pot;
  pin_t pin_light;
  pin_t pin_out;
  bool  out_high;
} chip_state_t;

static float clamp01(float x) {
  if (x < 0.0f) return 0.0f;
  if (x > 1.0f) return 1.0f;
  return x;
}

// light: 0 (tối) .. 1 (sáng) -> điện trở LDR, nội suy tuyến tính giữa các mốc
static float ldr_resistance(float light) {
  float pos = light * (TABLE_SIZE - 1);
  int i = (int)pos;
  if (i >= TABLE_SIZE - 1) return LDR_OHM[TABLE_SIZE - 1];
  float t = pos - (float)i;
  return LDR_OHM[i] + (LDR_OHM[i + 1] - LDR_OHM[i]) * t;
}

static void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t *)user_data;

  // Chiết áp Wokwi là nguồn analog chuẩn nên đọc bằng ADC được (0..5V)
  float light = clamp01(pin_adc_read(chip->pin_light) / VCC_VOLT);
  float pot   = clamp01(pin_adc_read(chip->pin_pot) / VCC_VOLT);

  float r_ldr = ldr_resistance(light);
  float r_pot = R_POT_MAX * pot;
  if (r_pot < 1.0f) r_pot = 1.0f;

  float vb = VCC_VOLT * r_pot / (r_ldr + r_pot);

  bool want_high = chip->out_high ? (vb > VBE_OFF) : (vb >= VBE_ON);
  if (want_high != chip->out_high) {
    chip->out_high = want_high;
    pin_write(chip->pin_out, want_high ? HIGH : LOW);
  }
}

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  pin_init("VCC", INPUT);                 // chỉ để đi dây cho giống sơ đồ
  pin_init("GND", INPUT);
  chip->pin_pot   = pin_init("POT", ANALOG);
  chip->pin_light = pin_init("LIGHT", ANALOG);
  chip->pin_out   = pin_init("OUT", OUTPUT_LOW);
  chip->out_high  = false;

  const timer_config_t timer_config = {
    .callback = chip_timer_event,
    .user_data = chip,
  };
  timer_t timer_id = timer_init(&timer_config);
  timer_start(timer_id, 10000, true);     // cập nhật mỗi 10 ms
}