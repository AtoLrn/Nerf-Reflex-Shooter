#include <Servo.h>
#include "Adafruit_VL53L0X.h"

#define RXLED 17
#define BUZZER 7
#define TRIGGERED 130
#define RELEASE 170

Servo servo;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

bool shouldShoot = true;

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

void setup() {
  randomSeed(analogRead(0));
  pinMode(RXLED, OUTPUT);  
  pinMode(BUZZER, OUTPUT);
  Serial.begin(115200);
  servo.attach(14);
  servo.write(RELEASE);
  lox.begin();
  delay(1000);
  
  if (random(6) == 5) {
    tone(BUZZER, a, 500);
    delay(550);
    tone(BUZZER, a, 500); 
    delay(550);   
    tone(BUZZER, a, 500);
    delay(550); 
    tone(BUZZER, f, 350);
    delay(350); 
    tone(BUZZER, cH, 150);  
    delay(150); 
    tone(BUZZER, a, 500);
    delay(550); 
    tone(BUZZER, f, 350);
    delay(350); 
    tone(BUZZER, cH, 150);  
    delay(150); 
    tone(BUZZER, a, 650);
    delay(1000);
    tone(BUZZER, eH, 500);
    delay(550); 
    tone(BUZZER, eH, 500);
    delay(550); 
    tone(BUZZER, eH, 500);  
    delay(550); 
    tone(BUZZER, fH, 350);
    delay(350); 
    tone(BUZZER, cH, 150);
    delay(150); 
    tone(BUZZER, gS, 500);
    delay(550); 
    tone(BUZZER, f, 350);
    delay(350); 
    tone(BUZZER, cH, 150);
    delay(150); 
    tone(BUZZER, a, 650);
  }

  digitalWrite(RXLED, HIGH);
  delay(1000);
  digitalWrite(RXLED, LOW);
  delay(5000);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  
  lox.rangingTest(&measure, false);
  
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
        if (measure.RangeMilliMeter > 200 && measure.RangeMilliMeter < 3000 && shouldShoot){
        Serial.print("SHOOT");
        shoot();
        delay(9000);
    } 
  } else {
    //Serial.println(" out of range ");
  }
  delay(100);
}

void shoot(){
  servo.write(TRIGGERED);
  delay(1000);
  servo.write(RELEASE);
}