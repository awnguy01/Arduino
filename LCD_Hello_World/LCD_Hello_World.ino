#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);

void setup(){
  lcd.begin(16,2);
}

void loop() {
  lcd.clear();
  lcd.print("Hello World!");
  delay(1000);
}

