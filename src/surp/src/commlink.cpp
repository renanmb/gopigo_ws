#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include "surp/Int32Stamped.h"

class Link{
   public:
     Link(); //error: ISO C++ forbids declaration of ‘Imu’ with no type [-fpermissive]

   private:
     void velLinearCallback(const std_msgs::Float32::ConstPtr& vx);
     void velAngularCallback(const std_msgs::Float32::ConstPtr& wz);
     void encoderCallback(const std_msgs::Int32::ConstPtr& tk);
     void motor1_cmd_callback(const std_msgs::Float64::ConstPtr& mtx);
     void motor2_cmd_callback(const std_msgs::Float64::ConstPtr& mty);
     ros::NodeHandle nh;
     ros::Publisher pub1;
     ros::Publisher pub2;
     ros::Publisher pub3;
     ros::Publisher pub4;
     ros::Subscriber velLinear_x_sub;
     ros::Subscriber velAngular_z_sub;
     ros::Subscriber encoder_sub;
     ros::Subscriber motor1_cmd_sub;
     ros::Subscriber motor2_cmd_sub;
     geometry_msgs::Twist vel;
     //std_msgs::Int32 encoder;
		 surp::Int32Stamped encoder;
     ros::Time now_time =ros::Time::now();
     std_msgs::Float32 accel_x;
     std_msgs::Float32 accel_y;
    
};

//This will change when add the TF and pose 
Link::Link(){
   pub1 = nh.advertise<geometry_msgs::Twist> ("/comm_drive_robot", 10 );
   pub2 = nh.advertise<surp::Int32Stamped> ("/comm_encoder", 10);
   pub3 = nh.advertise<std_msgs::Float32> ("/comm_accel_x", 1);
   pub4 = nh.advertise<std_msgs::Float32> ("/comm_accel_y", 1);

   velLinear_x_sub = nh.subscribe<std_msgs::Float32> ("/accel_x", 1, &Link::velLinearCallback, this);
   velAngular_z_sub = nh.subscribe<std_msgs::Float32> ("/accel_z", 1, &Link::velAngularCallback, this);
   encoder_sub = nh.subscribe<std_msgs::Int32> ("encoder", 10, &Link::encoderCallback, this);
   motor1_cmd_sub = nh.subscribe<std_msgs::Float64> ("lwheel_angular_vel_motor", 10, &Link::motor1_cmd_callback, this);
   motor2_cmd_sub = nh.subscribe<std_msgs::Float64> ("rwheel_angular_vel_motor", 10, &Link::motor2_cmd_callback, this);
}

//Encoder receives "encoder" and publish topic "/encoder" in Int32

void Link::velLinearCallback(const std_msgs::Float32::ConstPtr& vx){
  /* vel.angular.z = vx->data;
   pub.publish(vel); */
   accel_x.data = vx->data;
   pub3.publish(accel_x);
  
}

void Link::velAngularCallback(const std_msgs::Float32::ConstPtr& wz){
/* vel.linear.x = -1 * wz->data; //change this message
   pub.publish(vel); */
   accel_y.data = wz->data;
   pub4.publish(accel_y);
   
}

void Link::encoderCallback(const std_msgs::Int32::ConstPtr& tk){
   
   encoder.data = tk->data;
	 encoder.header.stamp = now_time; 
   pub2.publish(encoder); //need to review how to do this
}

void Link::motor1_cmd_callback(const std_msgs::Float64::ConstPtr& mtx){
   vel.linear.x = mtx->data; //convert the motor1_cmd from Float32 to Float64
   pub1.publish(vel);
}

void Link::motor2_cmd_callback(const std_msgs::Float64::ConstPtr& mty){
   vel.linear.y = mty->data; //convert the motor2_cmd from Float32 to Float64
   pub1.publish(vel);
}

int main(int argc, char** argv){
   ros::init(argc, argv, "commlink");
   Link Link; //object did not understand why
   ros::spin();
}
