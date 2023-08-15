#define BLYNK_TEMPLATE_ID "TMPLAxQ6X-up"
#define BLYNK_DEVICE_NAME "NODEMCU"
#define BLYNK_AUTH_TOKEN "RL8JHLtdGpBwlTGglD5keKqz2OAiEnHD"
#define MAX_SPEED 190 // sets speed of DC motors
#define MAX_SPEED_OFFSET 20
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <AFMotor.h> 
#include <Servo.h> 
#include <Adafruit_MotorShield.h>
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int speedSet =200;
char auth[] = "RL8JHLtdGpBwlTGglD5keKqz2OAiEnHD"; //Enter your Blynk application 
auth token
char ssid[] = "thewifi"; //Enter your WIFI name
char pass[] = "thepassword"; //Enter your WIFI passowrd
void setup() {
 Serial.begin(115200);
// pinMode(ENA, OUTPUT);
// pinMode(IN1, OUTPUT);
// pinMode(IN2, OUTPUT);
// pinMode(IN3, OUTPUT);
 //pinMode(IN4, OUTPUT);
 //pinMode(ENB, OUTPUT);
 Blynk.begin(auth, ssid, pass);
}
BLYNK_WRITE(V0) {
 forward = param.asInt();
}
BLYNK_WRITE(V1) {
 backward = param.asInt();
}
BLYNK_WRITE(V2) {
 left = param.asInt();
}
BLYNK_WRITE(V3) {
 right = param.asInt();
}
BLYNK_WRITE(V4) {
 speedSet = param.asInt();
}
void smartcar() {
 if (forward == 1) {
 carforward();
 Serial.println("carforward");
 } else if (backward == 1) {
 carbackward();
 Serial.println("carbackward");
 } else if (left == 1) {
 carturnleft();
 Serial.println("carfleft");
 } else if (right == 1) {
 carturnright();
 Serial.println("carright");
 } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
 carStop();
 Serial.println("carstop");
 }
}
void loop() {
 Blynk.run();
 smartcar();
}
void moveStop() {
 motor1.run(RELEASE); 
 motor2.run(RELEASE);
 motor3.run(RELEASE);
 motor4.run(RELEASE);
 } 
 
void moveForward() {
if(!goesForward)
 {
 goesForward=true;
 motor1.run(FORWARD); 
 motor2.run(FORWARD);
 motor3.run(FORWARD); 
 motor4.run(FORWARD); 
 for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to 
avoid loading down the batteries too quickly
 {
 motor1.setSpeed(speedSet);
 motor2.setSpeed(speedSet);
 motor3.setSpeed(speedSet);
 motor4.setSpeed(speedSet);
 delay(5);
 }
 }
}
void moveBackward() {
 goesForward=false;
 motor1.run(BACKWARD); 
 motor2.run(BACKWARD);
 motor3.run(BACKWARD);
 motor4.run(BACKWARD); 
 for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to 
avoid loading down the batteries too quickly
 {
 motor1.setSpeed(speedSet);
 motor2.setSpeed(speedSet);
 motor3.setSpeed(speedSet);
 motor4.setSpeed(speedSet);
 delay(5);
 }
} 
void turnRight() {
 motor1.run(RELEASE);
 motor2.run(FORWARD);
 motor3.run(FORWARD);
 motor4.run(RELEASE); 
 delay(2000);
 motor1.run(FORWARD); 
 motor2.run(FORWARD);
 motor3.run(FORWARD);
 motor4.run(FORWARD); 
} 
void turnLeft() {
 motor1.run(FORWARD); 
 motor2.run(RELEASE); 
 motor3.run(RELEASE);
 motor4.run(FORWARD); 
 delay(2000);
 motor1.run(FORWARD); 
 motor2.run(FORWARD);
 motor3.run(FORWARD);
 motor4.run(FORWARD);
} 
