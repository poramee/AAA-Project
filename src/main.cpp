#include <NewPing.h>
#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

NewPing sonar1(D2,D3,100),sonar2(D5,D6,100);
Servo servo;

char auth[] = "513def663a7a4b32b4c439010ab583aa";
char ssid[] = ":0";
char pass[] = "HelloWorld";

int surroundings[200];

double ping,ping2;

void process();

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  servo.attach(D1);
  for(int i = 0;i < 180;++i){
    surroundings[i] = sonar1.ping_cm();
    servo.write(i);
    delay(10);
  }
}

void loop()
{
  for(int i = 0;i < 180;++i){
    process();
    servo.write(i);
  }
  for(int i = 180;i > 0;--i){
    process();
    servo.write(i);
  }  
}

void process(){
    do{
      ping = 0;
      ping2 = 0;
      // ping = sonar1.ping_cm();
      for(int a = 0;a < 5;++a){
        ping += sonar1.ping_cm();
        ping2 += sonar2.ping_cm();
        delay(1);
      }
      ping /= 5;
      ping2 /= 5;
      Serial.print(ping2);
      Serial.print("\t");
      Serial.println(ping);
    }while(ping < 20); 
}