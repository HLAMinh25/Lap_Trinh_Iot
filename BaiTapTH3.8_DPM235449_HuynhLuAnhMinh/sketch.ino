/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-lm35-temperature-sensor
 */

void setup() {
    for (int i = 2; i < 10; i++) {
        pinMode(i, OUTPUT);
    }
}

void allLEDsOff(void) {
    for (int i = 2; i < 10; i++) {
        digitalWrite(i, LOW);
    }
}

void loop() {
    for (int i = 2; i < 9; i++) {
        allLEDsOff();
        digitalWrite(i, HIGH);
        delay(200);
    }

    for (int i = 9; i > 2; i--) {
        allLEDsOff();
        digitalWrite(i, HIGH);
        delay(200);
    }
}