const float voltageDelay = 5000.0;
float lastCheckedVoltageTime = 0.0;

int reading=0;
int relayPin = 7;
float voltage=0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  
  Serial.begin(9600);
}

void loop() {
    if((millis()>voltageDelay + lastCheckedVoltageTime) || lastCheckedVoltageTime == 0.0) {
    digitalWrite(relayPin, HIGH);
    delay(100);
    reading = analogRead(A0);
    voltage = (float)reading*(10/1024);
    digitalWrite(relayPin, LOW);
    Serial.println(voltage,2);

    lastCheckedVoltageTime = millis();
  }
}
