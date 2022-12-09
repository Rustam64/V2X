#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include<AFMotor.h>           

//our L298N control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

//sensor pins
#define trig_pin A3 //analog input 1
#define echo_pin A2 //analog input 2
#define maximum_distance 200

boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name

  AF_DCMotor Motor1(1,MOTOR12_1KHZ);
  AF_DCMotor Motor2(2,MOTOR12_1KHZ);
  AF_DCMotor Motor3(3,MOTOR34_1KHZ);
  AF_DCMotor Motor4(4,MOTOR34_1KHZ);
void setup(){
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 30){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  
  Motor1.setSpeed(0);    //define motor1 speed:
  Motor1.run(RELEASE);   //stop motor1:
  Motor2.setSpeed(0);    //define motor2 speed:
  Motor2.run(RELEASE);   //stop motor2:
  Motor3.setSpeed(0);    //define motor3 speed:
  Motor3.run(RELEASE);   //stop motor3:
  Motor4.setSpeed(0);    //define motor4 speed:
  Motor4.run(RELEASE);   //stop motor4:
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
  Motor1.setSpeed(200);  //define motor1 speed:
  Motor1.run(FORWARD);   //rotate motor1 clockwise:
  Motor2.setSpeed(200);  //define motor2 speed:
  Motor2.run(BACKWARD);   //rotate motor2 clockwise:
  Motor3.setSpeed(200);  //define motor3 speed:
  Motor3.run(BACKWARD);   //rotate motor3 clockwise:
  Motor4.setSpeed(200);  //define motor4 speed:
  Motor4.run(FORWARD);   //rotate motor4 clockwise:
  }
}

void moveBackward(){

  goesForward=false;

  Motor1.setSpeed(200);  //define motor1 speed:
  Motor1.run(BACKWARD);   //rotate motor1 clockwise:
  Motor2.setSpeed(200);  //define motor2 speed:
  Motor2.run(FORWARD);   //rotate motor2 clockwise:
  Motor3.setSpeed(200);  //define motor3 speed:
  Motor3.run(FORWARD);   //rotate motor3 clockwise:
  Motor4.setSpeed(200);  //define motor4 speed:
  Motor4.run(BACKWARD);   //rotate motor4 clockwise:
  
}

void turnRight(){

  Motor1.setSpeed(200);  //define motor1 speed:
  Motor1.run(BACKWARD);  //rotate motor1 anticlockwise:
  Motor2.setSpeed(200);  //define motor2 speed:
  Motor2.run(FORWARD);  //rotate motor2 anticlockwise:
  Motor3.setSpeed(200);  //define motor3 speed:
  Motor3.run(BACKWARD);   //rotate motor3 clockwise:
  Motor4.setSpeed(200);  //define motor4 speed:
  Motor4.run(FORWARD);   //rotate motor4 clockwise:
  delay(450);
  
}

void turnLeft(){

  Motor1.setSpeed(200);  //define motor1 speed:
  Motor1.run(FORWARD);   //rotate motor1 cloclwise:
  Motor2.setSpeed(200);  //define motor2 speed:
  Motor2.run(BACKWARD);   //rotate motor2 clockwise:
  Motor3.setSpeed(200);  //define motor3 speed:
  Motor3.run(FORWARD);  //rotate motor3 anticlockwise:
  Motor4.setSpeed(200);  //define motor4 speed:
  Motor4.run(BACKWARD);  //rotate motor4 anticlockwise:
  delay(450);
}
