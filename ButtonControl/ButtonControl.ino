
/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

#include <LiquidCrystal.h>

// the setup routine runs once when you press reset:

LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );

int UP_RES = 143;
int DOWN_RES = 329;
int LEFT_RES = 505;
int RIGHT_RES = 0;
int SEL_RES = 742;
int oldSensorValue = 0;
int buffer = 5;
String buttonText = "";

boolean displayToggle = true;
void setup() {
  // initialize serial communication at 9600 bits per second:

  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  
}


// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
    delay(10);
  
  if(sensorValue != 1023){
 //   oldSensorValue = sensorValue;
    buttonText = readButton(sensorValue);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(buttonText);
    if(buttonText == "Select"){
      toggleDisplay();
    }
      
    delay(100);
    
  }
}
void toggleDisplay(){
  displayToggle = !displayToggle;
  int i;

  if(displayToggle){
      for(i = 0 ; i < 256; i++){
        analogWrite(3, i);        
        delay(4);
      }     
   }
   else{
      for(i = 255; i > 0; i--){
        analogWrite(3, i);        
        delay(4);
      }     
   }
     
}
String readButton(int value){
  if(value < UP_RES + buffer && value > UP_RES - buffer){
    return "Up";
  }
  else if(value < DOWN_RES + buffer && value > DOWN_RES - buffer){
    return "Down";
  }
  else if(value < LEFT_RES + buffer && value > LEFT_RES - buffer){
    return "Left";
  }
  else if(value < RIGHT_RES + buffer && value > RIGHT_RES - buffer){
    return "Right";
  }
  else if(value < SEL_RES + buffer && value > SEL_RES - buffer){
    return "Select";
  }
  else
  {
    return ""; 
  }
}
