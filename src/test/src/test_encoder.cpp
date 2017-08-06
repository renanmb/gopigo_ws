#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <math.h>

std_msgs::Int32 encoder;
ros::Subscriber encoder_sub;
ros::Publisher vel_pub;
geometry_msgs::Twist vel;		

//make subscriber from comm encoder
void encoderCallback(const std_msgs::Int32::ConstPtr& tk){
   
   encoder.data = tk->data; 
   vel.linear.x = float((encoder.data*3.1529*pow(10,-2))+0.051);
   vel_pub.publish(vel);
}


//make publisher for cmd_vel

//create a rotary encoder to send cmd_vel

int main(int argc, char** argv){
   ros::init(argc, argv, "test_encoder");
   ros::NodeHandle nh;
   vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
   encoder_sub = nh.subscribe<std_msgs::Int32> ("comm_encoder", 10, &encoderCallback); 
		

   ros::spin();

   return 0;
}
