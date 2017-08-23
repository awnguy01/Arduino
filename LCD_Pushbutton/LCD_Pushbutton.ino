#include<LiquidCrystal.h>

LiquidCrystal lcd(8,9,10,11,12,13);

//Pin labels
const int interruptPin = 2;  //input pin to be interrupted

//Global variables
int breakCount = 0;          //number of times IR sensor is interrupted
unsigned long startTime = 0; //time to start each RPM calculation
unsigned long endTime = 0;   //time to end each RPM calculation
float rpm = 0;               //windmill revolutions per minute
float numberOfBlades = 4;    //number of windmill blades
float motorEff = 0;          //efficiency of the motor
float sysEff = 0;            //efficiency of the system
float tIn = 0;               //torque of the windmill
float tOut = 0;              //torque of the DC motor
float pInMotor = 0;          //power of the motor input
float pIn = 0;               //power of the windmill
float pOut = 0;              //power of the DC motor

int displaySetting = 1;                       //default LCD display setting (RPM)
const int MAX_DISPLAYS = 3;                   //total number of LCD display settings
const int buttonPin = 3;                      //input pin for pushbutton
unsigned long lastDisplaySwitch = millis ();  //marks time that the last time LCD setting was changed
const int DISPLAY_DELAY = 250;                //delay time before LCD setting can be changed

void setup() {
  
  lcd.begin(16,2);    //LCD setup
  lcd.display();

  pinMode(interruptPin, INPUT);                                          //IR interrupt setup
  attachInterrupt(digitalPinToInterrupt(interruptPin), broken, FALLING); //broken function called each time interrupt pin has falling signal
  
  pinMode(buttonPin, INPUT); //changes the LCD display every time the button is pressed
  attachInterrupt(digitalPinToInterrupt(buttonPin), changeDisplaySetting, FALLING);

  Serial.begin(9600);  //Serial interface for debugging
}

void loop() { 

   if (breakCount >= 30) {                                            //calculates rpm every 30 interruptions
    endTime = millis();                                               //records the time for 30 interruptions
    rpm = ((breakCount/numberOfBlades)/(endTime - startTime))*60000;  //calculates revolutions per minute
    Serial.println(rpm);                                              //prints rpm on serial monitor for debugging
    breakCount = 0;                                                   //resets number of recorded interruptions to 0
  }
  
  pOutCalc();    //runs function to calculate power output
  sysEffCalc();  //runs function to calcualte system efficiency
  
  delay(1000);     
  displayLCD(); //Only changes LCD display once per second
}

void broken() {             //function run each time IR interruption occurs
  if (breakCount == 0) {
    startTime = millis();   //resets the start time for each new interval of 30 interruptions
    Serial.print(startTime);
  }
  breakCount++;             //adds 1 to breakCount each time IR interruption occurs
}

void pOutCalc() {                                          //function used to calculate power output
  tOut = ((rpm-1600)/(-5))*0.0000980665;                                //torque output equation
  pInMotor = -0.000428*tOut*tOut+0.136943*tOut+0.000739;    //motor power input equation
  if (tOut<=48) {                                          //motor efficiency equations
    motorEff = -0.001618*tOut*tOut+0.363542*tOut+49.376500;
  }
  else {
    motorEff = -0.000434*tOut*tOut-0.072269*tOut+67.566800;
  }
  pOut = motorEff*pInMotor;                                //power output equation in watts
}

void sysEffCalc() {                        //function used to calculate system efficiency
  tIn = 8*tOut;               //torque input equation
  pIn = (tIn*rpm)/9549;                      //power input equation
  sysEff = (pOut/pIn)/2;            //converts power output to kilowatts and calculates system efficiency percentage
}

void displayLCD()         //called whenever the LCD is called to be updated
{
  switch(displaySetting)  //changes LCD display depending on number of button presses
  {
    case 1:
      lcd.clear();        //clears LCD screen
      lcd.print(rpm);     //displays rpm value
      lcd.print(" RPM");   //includes units
      break;              //exits switch statement
    case 2:
      lcd.clear();        //clears LCD screen
      lcd.print(pOut);    //displays power output in watts
      lcd.print(" W");     //includes units
      break;              //exits switch statement
    case 3:
      lcd.clear();        //clears LCD screen
      lcd.print(sysEff);  //displays system efficiency percentage
      lcd.print(" %");     //includes percentage sign
      break;              //exits switch statement
    default:
      lcd.clear();                      //clears LCD screen
      lcd.print("Unknown Setting!");    //displays this if unknown input is received by the button input pin
  }
}

void changeDisplaySetting()
{
  if(lastDisplaySwitch + DISPLAY_DELAY < millis()) {   //Only lets you switch display every DISPLAY_DELAY milliseconds
    lastDisplaySwitch = millis();
    Serial.println("Switching display");
    displaySetting++;
    if(displaySetting > MAX_DISPLAYS) {
      displaySetting = 1;
    }
    displayLCD();
  }
}



