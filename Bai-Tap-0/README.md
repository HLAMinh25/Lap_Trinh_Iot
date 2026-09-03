\# BÀI TẬP 0: TỔNG QUAN PHẦN CỨNG VÀ MÔ PHỎNG IOT



1\. Cấu trúc thư mục bài nộp



\* \*\*`01-Blink/`\*\*: Dự án mô phỏng mạch chớp tắt LED điều khiển qua chân Digital 13 trên Wokwi.

\* \*\*`02-Weather/`\*\*: Dự án mô phỏng đọc cảm biến nhiệt độ \& độ ẩm DHT22 trên Wokwi.

\* \*\*`Blink/`\*\*: File mã nguồn gốc Arduino IDE (`.ino`).

\* \*\*`Nội dung tìm hiểu về các board mạch trong Lập Trình IOT.docx`\*\*: File báo cáo lý thuyết chi tiết.



\---



2\. Tìm hiểu các Board mạch trong IoT



\### a. Arduino UNO R3

\* \*\*Vi điều khiển:\*\* ATmega328P (8-bit RISC, Flash 32KB, SRAM 2KB, EEPROM 1KB, tần số 16MHz, điện áp hoạt động 5V).\[cite: 1]

\* \*\*Cổng giao tiếp \& Chân I/O:\*\*

&#x20; \* 14 chân Digital I/O (chân 0/1 làm UART RX/TX).\[cite: 1]

&#x20; \* 6 chân PWM (3, 5, 6, 9, 10, 11) hỗ trợ điều chế độ rộng xung.\[cite: 1]

&#x20; \* 6 chân Analog (A0 - A5) đọc tín hiệu điện áp biến thiên qua ADC 10-bit.\[cite: 1]

\* \*\*Nguồn cấp:\*\* Cổng USB Type-B (5V) và Jack DC (khuyên dùng 7-12V), tích hợp IC ổn áp 5V và 3.3V (50mA).\[cite: 1]



\### b. Raspberry Pi

\* \*\*CPU \& RAM:\*\* Vi xử lý ARM đa nhân kèm RAM lớn (1GB - 4GB), hoạt động như một máy tính hoàn chỉnh chạy hệ điều hành Linux/Raspberry Pi OS.\[cite: 1]

\* \*\*Kết nối:\*\* Tích hợp Wi-Fi, Ethernet RJ45, Bluetooth và cổng USB Host, đóng vai trò làm \*\*IoT Gateway\*\* kết nối Cloud.\[cite: 1]



\### c. ESP8266 \& ESP32

\* \*\*Kết nối không dây:\*\* Tích hợp SoC Wi-Fi / Bluetooth trực tiếp trên bo mạch.\[cite: 1]

\* \*\*Ưu điểm:\*\* Giá thành rẻ, hiệu năng xử lý cao, tối ưu cho việc triển khai các thiết bị IoT diện rộng.\[cite: 1]



\---



3\. Điện trở, LED và Cảm biến



\### a. Điện trở (Resistor) \& LED

\* \*\*Điện trở:\*\* Linh kiện cản trở dòng điện theo định luật Ohm ($R = U/I$), dùng để hạn dòng và bảo vệ LED (thường dùng $220\\Omega - 330\\Omega$).\[cite: 1]

\* \*\*LED (Light Emitting Diode):\*\* Đi-ốt phát quang gồm 2 cực Anode (+) và Cathode (-), dùng làm thiết bị đầu ra báo hiệu trạng thái.\[cite: 1]



\### b. Cảm biến thông dụng



| Tên cảm biến | Chuẩn tín hiệu | Ứng dụng thực tế |

| :--- | :--- | :--- |

| \*\*DHT11 / DHT22\*\* | Digital\[cite: 1] | Đo nhiệt độ và độ ẩm không khí\[cite: 1] |

| \*\*LDR (Quang trở)\*\* | Analog\[cite: 1] | Đo cường độ ánh sáng, bật tắt đèn tự động\[cite: 1] |

| \*\*PIR (HC-SR501)\*\* | Digital\[cite: 1] | Cảm biến chuyển động thân nhiệt hồng ngoại\[cite: 1] |

| \*\*MQ-2\*\* | Analog / Digital\[cite: 1] | Phát hiện rò rỉ khí gas, khói và khí dễ cháy\[cite: 1] |



\---



4\. Kết quả thực hành mô phỏng



\* \*\*Bài 01 (Blink):\*\* Mô phỏng thành công mạch chớp tắt LED ngoài kết hợp điện trở hạn dòng trên nền tảng Wokwi.

\* \*\*Bài 02 (Weather):\*\* Đọc thành công dữ liệu nhiệt độ (°C) và độ ẩm (%) từ cảm biến DHT22 xuất ra Serial Monitor.

