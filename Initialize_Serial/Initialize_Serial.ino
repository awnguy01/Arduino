void setup() {
  //Initialize  LED pin
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); //Turn LED on

  //Initialize serial
  Serial.begin(9600);
}
void loop() {
  delay(1000);
  digitalWrite(13, LOW); //Turn LED off
  delay(1000);
  digitalWrite(13, HIGH); //Turn LED on

  Serial.println("Blink");
}
