/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-lm35-temperature-sensor
 */

const int kPinPot = A0;
const int kPinLed = 9;
const int kPinButton1 = 2;
const int kPinButton2 = 3;

int ledBrightness = 128;

void setup(){
    pinMode(kPinLed, OUTPUT);
    pinMode(kPinButton1, INPUT);
    pinMode(kPinButton2, INPUT);
    digitalWrite(kPinButton1, HIGH);
    digitalWrite(kPinButton2, HIGH);
}

long lastTime = 0;
int ledValue = LOW;

void loop(){
    int sensorValue;
    sensorValue = analogRead(kPinPot);
    if (digitalRead(kPinButton1) == LOW){
        ledBrightness--;
    }
    if (digitalRead(kPinButton2) == LOW){
        ledBrightness++;
    }

    ledBrightness = constrain(ledBrightness, 0, 255);
    if (millis() > lastTime + sensorValue){
        if (ledValue == LOW){
            ledValue = HIGH;
        }
        else{
            ledValue = LOW;
        }
        lastTime = millis();
    }
 
    if (ledValue == HIGH){
        analogWrite(kPinLed, ledBrightness);
    }
    else{
        analogWrite(kPinLed, 0);
    }
}