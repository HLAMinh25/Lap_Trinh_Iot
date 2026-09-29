// bc547.chip.c - Transistor NPN BC547 (mô hình công tắc, logic số) cho Wokwi
// Chân: B (base), C (collector), E (emitter). Nối E xuống GND như trong sơ đồ.
//
// Vì sao dùng logic số? Wokwi là trình mô phỏng số, chỉ có analog rất hạn chế
// (không giải được mạng điện trở), nên chip không đọc điện áp analog nữa:
//   - B ở mức CAO (tương đương Vbe >= ~0.65V) -> transistor dẫn -> kéo chân C xuống GND.
//   - B ở mức THẤP                            -> transistor ngắt -> chân C thả nổi.
//
// Thuộc tính (đặt trong diagram.json, phần attrs của chip):
//   basePullup = 1 : bật điện trở kéo lên bên trong cho chân B. Dùng cho Q2, thay cho
//                    đường 5V - 1K - base Q2 (Wokwi không mô phỏng được dòng qua điện trở).

#include "wokwi-api.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  pin_t pin_b;
  pin_t pin_c;
  pin_t pin_e;
  bool  on;
} chip_state_t;

static void set_collector(chip_state_t *chip, bool on) {
  chip->on = on;
  if (on) {
    pin_mode(chip->pin_c, OUTPUT_LOW);   // bão hòa: C xuống GND
  } else {
    pin_mode(chip->pin_c, INPUT);        // ngắt: C thả nổi
  }
}

static void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t *)user_data;
  bool want_on = pin_read(chip->pin_b) == HIGH;
  if (want_on != chip->on) {
    set_collector(chip, want_on);
  }
}

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->pin_b = pin_init("B", INPUT);
  chip->pin_c = pin_init("C", INPUT);
  chip->pin_e = pin_init("E", INPUT);
  chip->on = false;

  uint32_t pullup_attr = attr_init("basePullup", 0);
  if (attr_read(pullup_attr) != 0) {
    pin_mode(chip->pin_b, INPUT_PULLUP);
  }

  const timer_config_t timer_config = {
    .callback = chip_timer_event,
    .user_data = chip,
  };
  timer_t timer_id = timer_init(&timer_config);
  timer_start(timer_id, 1000, true);     // kiểm tra mỗi 1 ms
}