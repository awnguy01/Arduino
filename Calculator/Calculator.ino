int num1;
int num2;
String calc;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while(!Serial.available()) {
    //Do Nothing
  }
  if(Serial.available())
    {
      num1 = Serial.parseInt();
      Serial.println(num1);
    }
   while(!Serial.available()){
    //Do Nothing
  }
   if(Serial.available())
    {
      calc = Serial.readString();
      Serial.println(calc);
    }
    while(!Serial.available()) {
      //Do Nothing
    }
    if (Serial.available()) {
      num2 = Serial.parseInt();
      Serial.println(num2);
    }
        if (calc.equalsIgnoreCase("+"))
          {
            Serial.println(num1+num2);
          }
        else if (calc.equalsIgnoreCase("-"))
          {
            Serial.println(num1-num2);
          }
        else if (calc.equalsIgnoreCase("*"))
          {
            Serial.println(num1*num2);
          }
        else if (calc.equalsIgnoreCase("/"))
          {
            Serial.println(num1/num2);
          }
        else
          {
            Serial.println("Unknown operator");
          }
    }
