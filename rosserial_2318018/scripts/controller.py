#!/usr/bin/env python3

import rospy
from std_msgs.msg import Float32MultiArray
from geometry_msgs.msg import Twist


#callback function for subsriber
def clbk(sensor_msg):
	speed = sensor_msg.data[0]
	distance = sensor_msg.data[1] # collecting sensor data
	vel = Twist() #initialized a Twist variable

	#if distance is less than or equal to 20 then it will turn, else it will move forward
	if(distance <= 20):
		vel.linear.x=0
		vel.angular.z=speed
	else:
		vel.linear.x=speed
		vel.angular.z=0
	pub.publish(vel) #publish robot command to /cmd_vel
	

if __name__=='__main__':
	rospy.init_node('robot_controller',anonymous=True)
	pub = rospy.Publisher('/cmd_vel',Twist, queue_size=10)
	rospy.Subscriber('/sensor_data',Float32MultiArray, clbk)
	rospy.spin()

