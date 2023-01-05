#include "Arduino.h"
#include "LoRa_E32.h"
#include <SoftwareSerial.h>
#include <TimerOne.h>
#define relay 9
#define LAMP 7 
boolean lampState = HIGH;
String message = "";
#define PUMP 6 
boolean pumpState = HIGH;
#define FAN 5 
boolean fanState = HIGH;
#define CLEAN 8 
boolean cleanState = HIGH;
#define FEED 4 
boolean feedState = HIGH;
#define DRAIN 13
boolean drainState = HIGH;
int tep = 10;
int dir = 11;
int ena = 12;
int in1=A0;
int in2=A1;
int in3=A2;
int in4=A3;
String dieukhien = "";
String sendlamp ="";
String sendpump ="";
String sendfan ="";
String sendclean ="";
String senddrain ="";
String sendfeed ="";

SoftwareSerial mySerial(2, 3); 
LoRa_E32 e32ttl(&mySerial);
void setup()
{
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }
    e32ttl.begin();
    pinMode(relay, OUTPUT); 
    digitalWrite(relay, LOW);
    pinMode(LAMP, OUTPUT); 
    digitalWrite(LAMP, HIGH);
    pinMode(PUMP, OUTPUT); 
    digitalWrite(PUMP, HIGH);
    pinMode(FAN, OUTPUT); 
    digitalWrite(FAN, HIGH);
    pinMode(CLEAN, OUTPUT); 
    digitalWrite(CLEAN, HIGH);
    pinMode(DRAIN, OUTPUT); 
    digitalWrite(DRAIN, HIGH);
    pinMode(FEED, OUTPUT); 
    digitalWrite(FEED, HIGH);   
    pinMode(ena,OUTPUT); 
    pinMode(tep,OUTPUT); 
    pinMode(dir,OUTPUT);   
    digitalWrite(ena,LOW); 
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
      
    delay(100); 
}

void DIEUKHIEN(){
       //------------LAMP
        if (message.indexOf("TATLAMP")>=0) {;
          if (lampState == LOW){
           digitalWrite(LAMP, HIGH);
           lampState = HIGH;
          }
        }
        if (message.indexOf("LAMP") >= 0) {
          digitalWrite(LAMP, !digitalRead(LAMP));
          lampState = LOW;                    
        }
           if (digitalRead(LAMP)==0) {
            sendlamp = "BATLAMP"; 
           }else {
            sendlamp = "TATLAMP";
           }
        //---------------

        //---------------PUMP
        if (message.indexOf("TATPUMP")>=0) {;
          if (pumpState == LOW){
           digitalWrite(PUMP, HIGH);
           pumpState = HIGH;
          }
        }
        if (message.indexOf("PUMP") >= 0) {
          digitalWrite(PUMP, !digitalRead(PUMP));
          pumpState = LOW;                    
        }
           if (digitalRead(PUMP)==0) {
            sendpump = "BATPUMP"; 
           }else {
            sendpump = "TATPUMP";
           } 
        //---------------
        
        //---------------FAN
        if (message.indexOf("TATFAN")>=0) {
          if (fanState == LOW){
           digitalWrite(FAN, HIGH);
           fanState = HIGH;
          }
        }
        if (message.indexOf("FAN") >= 0) {
          digitalWrite(FAN, !digitalRead(FAN));
          fanState = LOW;                    
        }
           if (digitalRead(FAN)==0) {
             sendfan = "BATFAN";
           }else {
            sendfan = "TATFAN"; 
           } 
        //---------------

      //---------------CLEAN
        if (message.indexOf("TATCLEAN")>=0) {
          if (cleanState == LOW){
           digitalWrite(CLEAN, HIGH);
           cleanState = HIGH;
          }
        }
        if (message.indexOf("CLEAN") >= 0) {
          digitalWrite(CLEAN, !digitalRead(CLEAN));
          cleanState = LOW;                    
        }
           if (digitalRead(CLEAN)==0) {
             sendclean = "BATCLEAN";
           }else {
            sendclean = "TATCLEAN"; 
           } 
        //---------------

   //---------------DRAIN
        if (message.indexOf("TATDRAIN")>=0) {
          if (drainState == LOW){
           digitalWrite(DRAIN, HIGH);
           drainState = HIGH;
          }
        }
        if (message.indexOf("DRAIN") >= 0) {
          digitalWrite(DRAIN, !digitalRead(DRAIN));
          drainState = LOW; 
             if (digitalRead(DRAIN)==0) {
                  digitalWrite(in1,HIGH);
                  digitalWrite(in2,LOW);
                  digitalWrite(in3,HIGH);
                  digitalWrite(in4,LOW);
                  delay(1000);
                  digitalWrite(in1,LOW);
                  digitalWrite(in2,LOW);
                  digitalWrite(in3,LOW);
                  digitalWrite(in4,LOW);                   
             senddrain = "BATDRAIN";
           }else {
                  digitalWrite(in1,LOW);
                  digitalWrite(in2,HIGH);
                  digitalWrite(in3,LOW);
                  digitalWrite(in4,HIGH);
                  delay(1000);
                  digitalWrite(in1,LOW);
                  digitalWrite(in2,LOW);
                  digitalWrite(in3,LOW);
                  digitalWrite(in4,LOW);
            senddrain = "TATDRAIN"; 
           }                    
        }
        //---------------

        //---------------FEED
        if (message.indexOf("TATFEED")>=0) {
          if (feedState == LOW){
           digitalWrite(FEED, HIGH);
           feedState = HIGH;
          }
        }
        if (message.indexOf("FEED") >= 0) {
          digitalWrite(FEED, !digitalRead(FEED));
          feedState = LOW; 
         digitalWrite(dir,HIGH); // Đặt Dir ở trạng thái HIGH
  for(int x = 0; x < 100; x++) // Cho chay 1 vong
  {
    digitalWrite(tep,HIGH); // Output high
    delayMicroseconds(1000);
    digitalWrite(tep,LOW); // Output low
    delayMicroseconds(1000);
  }                    
        }
           if (digitalRead(FEED)==0) {
             sendfeed = "BATFEED";
           }else {
            sendfeed = "TATFEED"; 
           } 
        //---------------
        dieukhien = sendlamp + ";" + sendpump + ";" + sendfan + ";" + sendclean + ";" + senddrain + ";" + sendfeed + ";";
        Serial.println(dieukhien);
   e32ttl.sendFixedMessage(0, 2, 0x04, dieukhien);
   delay(100);
}
void xulyAuto() {
    if (message.indexOf("ONP") >= 0) {
      if( pumpState == HIGH){
    digitalWrite(PUMP, LOW);
    pumpState == HIGH
      }      }
  else if(message.indexOf("OFFP") >= 0){
    pumpState = HIGH;
           digitalWrite(PUMP, HIGH);
          }
    }
}

// The loop function is called in an endless loop
void loop()
{
    if (e32ttl.available()  > 1){
      ResponseContainer rs = e32ttl.receiveMessage();
      message = rs.data;
      Serial.println(message);
      DIEUKHIEN();
      xulyAuto(); 
}
}

 
