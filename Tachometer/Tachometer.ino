//Pin labels
const int interruptPin = 2;

//Global variables
int breakCount = 0;
unsigned long startTime = 0;
unsigned long endTime = 0;
double rpm = 0;
double numberOfBlades = 4;

void setup() {

  Serial.begin(9600);
  //IR Interrupt Setup
  pinMode(interruptPin, INPUT);
  //Every time the interrupt pin has a falling signal, "broken" will be called
  attachInterrupt(digitalPinToInterrupt(interruptPin), broken, FALLING);
}

void loop () {

  if (breakCount >= 30) {
    endTime = millis();
    rpm = ((breakCount/numberOfBlades)/(endTime - startTime))*60000;
    Serial.println(rpm);
    breakCount = 0;
  }
}

void broken() {
  if (breakCount == 0) {
    startTime = millis();
  }
  breakCount++;
}

