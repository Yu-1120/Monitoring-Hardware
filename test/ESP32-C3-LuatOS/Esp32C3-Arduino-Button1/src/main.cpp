#include <Arduino.h>
#include <math.h>



void setup() {
  Serial.begin(9600);

  pinMode(9,INPUT);
  pinMode(8,INPUT);
  
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(13,INPUT_PULLUP);
  pinMode(12, OUTPUT);
  digitalWrite(12,LOW);
}

void loop() 
{


  int LEFT_KEY =  digitalRead(9);
  int DOWN_KEY =  digitalRead(5);
  int UP_KEY =  digitalRead(8);
  int RIGHT_KEY =  digitalRead(13);
  int CENTER_KEY =  digitalRead(4);
  digitalWrite(12,LOW);

   if(LEFT_KEY == LOW){ 
      delay(LEFT_KEY);
      if(CENTER_KEY == LOW){
      Serial.println(LEFT_KEY);
      Serial.println("LEFT_KEY LOW ");    
      digitalWrite(12,HIGH);
      }
  }
   if(DOWN_KEY == LOW){ 
      delay(500);
      if(DOWN_KEY == LOW){
      Serial.println(DOWN_KEY);
      Serial.println("DOWN_KEY LOW ");    
      digitalWrite(12,HIGH);
      }
  }
   if(UP_KEY == LOW){ 
      delay(500);
      if(UP_KEY == LOW){
      Serial.println(UP_KEY);
      Serial.println("UP_KEY LOW ");    
      digitalWrite(12,HIGH);
      }
  }
   if(RIGHT_KEY == LOW){ 
      delay(500);
      if(RIGHT_KEY == LOW){
      Serial.println(RIGHT_KEY);
      Serial.println("RIGHT_KEY LOW ");    
      digitalWrite(12,HIGH);
      }
  }
   if(CENTER_KEY == HIGH){   //原理是悬空的
      delay(500);
      if(CENTER_KEY == HIGH){
      Serial.println(CENTER_KEY);
      Serial.println("CENTER_KEY HIGH ");    
      digitalWrite(12,HIGH);
      }
  }
}
