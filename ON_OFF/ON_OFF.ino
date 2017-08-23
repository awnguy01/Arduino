String arduinoInput;

void setup() {
  pinMode(2, OUTPUT);  //LINE 1
  Serial.begin(9600); //LINE 2
}

void loop() {
     while(!Serial.available()) {
    //Do Nothing
   }
    if (Serial.available()){
    arduinoInput = Serial.readString(); //LINE 4

    if(arduinoInput.equalsIgnoreCase("ON"))  //LINE 5
       {
         Serial.println("Turning LED ON...");  //LINE 6
         digitalWrite(2, HIGH); //LINE 7
       }
     else if (arduinoInput.equalsIgnoreCase("OFF")) //LINE 8
        {
          Serial.println("Turning LED OFF..."); //LINE 9
          digitalWrite(2, LOW);
        }
      else  //LINE110
        {
          Serial.println("Unknown command!"); //LINE 11
        }
    }
 }


