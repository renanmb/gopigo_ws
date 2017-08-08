#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include "surp/Int32Stamped.h
#include <math.h>

//std_msgs::Int32 encoder;
surp::Int32Stamped encoder;
ros::Time timelapse;
ros::Subscriber encoder_sub;
ros::Publisher vel_pub;
geometry_msgs::Twist vel;		

//make subscriber from comm encoder
void encoderCallback(const surp::Int32Stamped::ConstPtr& tk){

//Modify this equation to be the Controller Function
	 timelapse = encoder.header.stamp - encoder.header.stamp;
   kd = (encoder.data - encoder.data)/timelapse;
   vel.linear.x = float(((encoder.data*234)*5886) + kd);
   encoder.data = tk->data;
   encoder.header.stamp = tk->header; 
   vel_pub.publish(vel);
}


//make publisher for cmd_vel

//create a rotary encoder to send cmd_vel

int main(int argc, char** argv){
   ros::init(argc, argv, "pd_controller");
   ros::NodeHandle nh;
   vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
   encoder_sub = nh.subscribe<std_msgs::Int32> ("comm_encoder", 10, &encoderCallback); 
		

   ros::spin();

   return 0;
}
