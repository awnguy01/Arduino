void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
}

void loop() {
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);
  digitalWrite(2,HIGH);
}
