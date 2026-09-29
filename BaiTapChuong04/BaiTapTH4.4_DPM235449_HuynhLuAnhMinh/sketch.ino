void setup() { Serial.begin(9600); }
void loop() {
  float ao  = analogRead(A0) * 5.0 / 1023.0;
  float qc1 = analogRead(A1) * 5.0 / 1023.0;
  float qc2 = analogRead(A2) * 5.0 / 1023.0;
  Serial.print("AO="); Serial.print(ao,2);
  Serial.print("  Q1:C="); Serial.print(qc1,2);
  Serial.print("  Q2:C="); Serial.println(qc2,2);
  delay(300);
}