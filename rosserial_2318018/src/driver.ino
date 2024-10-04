#include <ros.h>
#include <geometry_msgs/Twist.h>

#define IN1 2
#define IN2 3
#define ENA 4
#define IN3 5
#define IN4 6
#define ENB 7

ros::NodeHandle nh;

// direct movement and adjust speed of each motor driver
void adjustSpeed(uint8_t one, uint8_t two, uint8_t three, uint8_t four, float speed){
  digitalWrite(IN1, one);
  digitalWrite(IN2, two);
  digitalWrite(IN3, three);
  digitalWrite(IN4, four);
  analogWrite(ENA, speed*255);
  analogWrite(ENB, speed*255);
}

// controlling the motor in different situation
void driveMotor(const geometry_msgs::Twist& move_msg){
  float speed = move_msg.linear.x;
  float angle = move_msg.angular.z;
  if(speed==0){
    if(angle == 0) adjustSpeed(LOW, LOW, LOW, LOW, 0) 
    if(angle>0){
      adjustSpeed(LOW, HIGH, HIGH, LOW, angle);
    }
    else{
      adjustSpeed(HIGH, LOW, LOW, HIGH, angle);
   }
  }
  else if(speed>0){
    adjustSpeed(LOW,HIGH,LOW,HIGH, speed);
  }
  else{
    adjustSpeed(HIGH,LOW,HIGH,LOW, -speed);
  }
}

ros::Subscriber <geometry_msgs::Twist> driver_sub("cmd_vel", &driveMotor); //create a subscriber which will take info from /cmd_vel topic and call driveMotor function


void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(driver_sub);
  // configure all pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(1);
}
