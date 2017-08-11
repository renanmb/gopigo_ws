#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include "pd_controller/Int32Stamped.h"
#include <math.h>

pd_controller::Int32Stamped encoder;

ros::Subscriber encoder_sub;
ros::Publisher vel_pub;
geometry_msgs::Twist vel;		

// subscriber from comm encoder
void encoderCallback(const pd_controller::Int32Stamped::ConstPtr& tk){

//Modify this equation to be the Controller Function
	// double timelapse[10] = {0};
   double timelapse = encoder.header.stamp.toSec() -encoder.header.stamp.toSec();
   double kd = (double(encoder.data) - double(encoder.data))/timelapse;
   vel.linear.x = float(((encoder.data*234)*5886) + kd);
   encoder.data = tk->data;
   encoder.header = tk->header; 
   vel_pub.publish(vel);
}


//make publisher for cmd_vel

//create a rotary encoder to send cmd_vel

int main(int argc, char** argv){
   ros::init(argc, argv, "pd_controller");
   ros::NodeHandle nh;
   vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
   encoder_sub = nh.subscribe<pd_controller::Int32Stamped> ("comm_encoder", 10, &encoderCallback); 
		

   ros::spin();

   return 0;
}
