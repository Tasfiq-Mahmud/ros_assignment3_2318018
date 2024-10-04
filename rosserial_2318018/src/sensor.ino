#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#define POTEN_PIN A5
#define ECHO_PIN 4
#define TRIG_PIN 2

ros::NodeHandle nh;

std_msgs::Float32MultiArray array_msg;
ros::Publisher sensor_pub("sensor_data",&array_msg);
unsigned long potenValue,duration;
float mapValue,distance;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  nh.initNode();
  nh.advertise(sensor_pub);
  pinMode(POTEN_PIN, INPUT);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  //listen to echo pin
  duration = pulseIn(ECHO_PIN,HIGH); 
  //evaluate the distance
  distance = duration * .034 /2;

  potenValue = analogRead(POTEN_PIN); // read from analog pin A5 
  mapValue = float(map(potenValue, 0,1023,0,100))/100; //map poten value from 0 to 1
  array_msg.data[0]=mapValue;
  array_msg.data[1]=distance; //assign two values to array_msg

  sensor_pub.publish(&array_msg);
  nh.spinOnce();
  delay(1000);
}
