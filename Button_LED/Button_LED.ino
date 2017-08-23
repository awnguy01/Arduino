const int inPin = 3;
const int outPin = 2;

void setup() {
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, LOW);
}

void loop(){
  int input = digitalRead(inPin);
  digitalWrite(outPin,input);
}

