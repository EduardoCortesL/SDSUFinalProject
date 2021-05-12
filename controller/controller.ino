
// Arduino linear actuator Controller 
#include <LiquidCrystal.h>
#define fsrpin A0

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int Switch = 2;
int state = 0, Loadstate=0;
int fsrreading;

void setup() {
  
  Serial.begin(57600);
  lcd.begin(16, 2);  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);

  Serial.println("** Ready **");
  lcd.print("** Ready **");

}

void loop() { // Controls actuator and stoppage by excedding pressure limit 

  lcd.setCursor(0, 1);
  
  Serial.println("Slide Forward");
  setDir(1);
  slide(5);
  lcd.print("Actuator Sliding Forward");

  Serial.println("Slide Backward");
  setDir(2);
  slide(5);
  lcd.clear();
  lcd.print("Actuator Sliding Backwards"); 
  
  Serial.print(fsrreading); //sensor goes from 0 - 1023 with 1023 being the maximum, our limit was calculated to be equal to 800
  if (fsrreading < 1 ){    //we check the force sensor is workign correctly here and is getting a constant reading 
    Serial.print("Pressure is under treshold");
    lcd.setCursor(0,2);
    lcd.print("Pressure = OK ");
  } else if (fsrreading > 800){ 
    setDir(0);
    Serial.print("Pressure above treshold stopping process");
    lcd.clear();
    lcd.print("Pressure is above treshold aborting process");
  }
  
}

void setDir(int d) { //Set Direction of the actuator 
  switch(d) {
    case 0: // off
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
    break;
    case 1: // forward
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
    break;
    case 2:  // backward
    digitalWrite(2,LOW);
    digitalWrite(4,HIGH);
    break;
    case 3:  // locked
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    break;
  }
}


//  Code to gradually speed up, then gradually slow down actuator. 
void slide(int d) {
  for(int v=0;v<256;++v) {
    analogWrite(3,v);
    delay(d);
  }
  for(int v=255;v>=0;--v) {
    analogWrite(3,v);
    delay(d);
  }
}
