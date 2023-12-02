#include <Servo.h>

Servo servo;
int echo1 = 11;     // Echo pin of the first ultrasonic sensor
int trig1 = 10;     // Trigger pin of the first ultrasonic sensor
int echo2 = 7;      // Echo pin of the second ultrasonic sensor
int trig2 = 8;      // Trigger pin of the second ultrasonic sensor
int servopin = 9;
int distance1;
int distance2;
int duration1;
int duration2;
bool isDistance2Measured = false;  // Flag to track if distance2 has been measured



void setup() {
  Serial.begin(9600);  // Initialize serial communication
  servo.attach(servopin);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
}

void measureDistance2() {
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  isDistance2Measured = true;  // Set the flag to true after measuring distance2
}

void moveServoToPosition(int target) {
  int currentPos = servo.read();
  
  // Limit the target position to a maximum of 90 degrees
  target = min(target, 90);
   
   int Kp =5; 
   int KpNeg = -5; 

  // Determine the appropriate direction to move the servo
  int step = (target - currentPos > 0) ? Kp : KpNeg;
  
  for (int pos = currentPos; pos != target; pos += step) {
    
    // Limit the position to a maximum of 90 degrees
    pos = min(pos, 90);
    servo.write(pos);
    delay(20);  
  }
}

void loop() {
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  Serial.print("Distance Sensor 1: ");
  Serial.print(distance1);
  Serial.print(" cm | ");

  // Check if distance2 has been measured
  if (!isDistance2Measured) {
    measureDistance2();  // Measure distance2 if not already measured
  }

  Serial.print("Distance Sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  int targetPos;
  int servoHoek;

  if (distance1 < 30 && distance1 > 0) {
    targetPos = 4* distance2;
  
if(targetPos >80 && targetPos<=90)
{
    servoHoek=90; 
}
if(targetPos >70 && targetPos<=80)
{
    servoHoek=80; 
}
if(targetPos >60 && targetPos<=70)
{
    servoHoek=70; 
}
if(targetPos>50 && targetPos<=60)
{
    servoHoek=60; 
}
if(targetPos >40 && targetPos<=50)
{
    servoHoek=50; 
}
if(targetPos >30 && targetPos<=40)
{
    servoHoek=40; 
}
if(targetPos >20 && targetPos<=30)
{
    servoHoek=30; 
}
if(targetPos >10 && targetPos<=20)
{
    servoHoek=20; 
}
if(targetPos >0 && targetPos<=10)
{
    servoHoek=10; 
}

    isDistance2Measured = false;  // Reset the flag for the next iteration
  } else {
    servoHoek = 0;
  }

  Serial.print("Target Position: ");
  Serial.println(servoHoek);

  
  // Move the servo smoothly to the new target position
  moveServoToPosition(servoHoek);

  delay(2000);  // Adjust the delay as needed
  

}
