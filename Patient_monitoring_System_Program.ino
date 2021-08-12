#include <LiquidCrystal.h>
#include <TimerOne.h>
#include "pitches.h"
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int buzzer=6;
int val;
int cel;
int mv;
int tempPin = A0;// temperature Sensor Pin
int HBSensor = A1;// Sensor Pin
int HBCount = 0;
int HBCheck = 0;
int TimeinSec = 0;
int HBperMin = 0;
int HBStart = 2;
int HBStartCheck = 0;
int ledPin=7;
int yellowPin=4;
int melody[]={NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int noteDurations[]={4, 8, 8, 4, 4, 4, 4, 4};


//float mv = (val/1024.0)*5000;
//float cel = mv/10;
//#void (*reset)(void)=0;
//if (cel<=37){
    //"restart lcd"
  //}
//}
void setup() {
  // put your setup code here, to run once:
 
  lcd.begin(20, 4);
  pinMode(buzzer,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(yellowPin,OUTPUT);
  pinMode(HBSensor, INPUT);
  pinMode(HBStart, INPUT_PULLUP);
  Timer1.initialize(800000); 
  Timer1.attachInterrupt( timerIsr );
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current HB  : ");
  lcd.setCursor(0,1);
  lcd.print("Time in Sec : ");
  lcd.setCursor(0,2);
  lcd.print("HB per Min  : 0.0");
  lcd.setCursor(0,3);
  lcd.print("Body Temp  : ");
  delay(1000);

  
}

void loop() {
  

  
 
  
  
  if(digitalRead(HBStart) == LOW){
  //lcd.setCursor(0,3);
  //lcd.print("HB Counting ..");
HBStartCheck = 1;}
  if(HBStartCheck == 1)
  {
      if((analogRead(HBSensor) == HIGH) && (HBCheck == 0))
      {
        HBCount = HBCount + 1;
        HBCheck = 1;
        lcd.setCursor(14,0);
        lcd.print(HBCount);
        lcd.print(" ");
      }
      if((analogRead(HBSensor) == LOW) && (HBCheck == 1))
      {
        HBCheck = 0;   
      }
      if(TimeinSec == 20)
      {
          HBperMin = HBCount * 6;
          HBStartCheck = 0;
          lcd.setCursor(14,2);
          lcd.print(HBperMin);
          lcd.print(" ");
          //lcd.setCursor(0,3);
          //lcd.print("Press Button again.");
          HBCount = 0;
          TimeinSec = 0;      
      }
  }
  
   val = analogRead(tempPin);
   mv = (val/1024.0)*5000;
   cel = mv/10;
  lcd.setCursor(14,3);
 
  if (cel >= 37)
  {
      lcd.clear();
  lcd.begin(1,0);
  lcd.print("Kondisi tidak normal");
  delay(1000);
  lcd.clear();
          
    digitalWrite(ledPin,HIGH);
    delay(100);
    digitalWrite(yellowPin,LOW);
    delay(100);
    digitalWrite(ledPin,LOW);
    delay(100);
    digitalWrite(yellowPin,HIGH);
    delay(100);
    
    
    
     for (int thisNote=0; thisNote <buzzer; thisNote++){

      //to calculate the note duration, take one second. Divided by the note type
      int noteDuration = 1000 / noteDurations [thisNote];
      tone(buzzer, melody [thisNote], noteDuration);

      //to distinguish the notes, set a minimum time between them
      //the note's duration +30% seems to work well
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(buzzer);

      //stop the tone playing
      noTone(buzzer);
     
    }
    
    }
    else  {
          lcd.print(" ");
          lcd.print(cel);
          digitalWrite(ledPin,LOW);
          digitalWrite(yellowPin,LOW);
          noTone(buzzer);
          
           
  }

 
}

void timerIsr()
{
  if(HBStartCheck == 1)
  {
      TimeinSec = TimeinSec + 1;
      lcd.setCursor(14,1);
      lcd.print(TimeinSec);
      lcd.print(" ");
  }
}
