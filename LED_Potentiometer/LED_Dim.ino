const int inPin = A0;
const int outPin = 2;
int power = 0;
void setup() {
  Serial.begin(9600);
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, LOW);
}

void loop () {
  power = analogRead(inPin);
  if (power>=500){
    digitalWrite(outPin, HIGH);
  }
  else {
    digitalWrite(outPin, LOW);
  }
  Serial.println(analogRead(inPin));
}

