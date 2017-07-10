# gopigo_ws

Using ROS with a GoPiGo differential drive robot

For more information on running the code:
http://www.moorerobots.com

Compatability: 

->Software
   ROS: Kinetic
   
   OS: Ubuntu 16.04
   
->Hardware
   Differential Drive Robot: GoPiGo
   
   WiFi USB Stick: Raspberry Pi USB WiFi Dongle


# Different Hardware - No Problem!

If you have a different type of robot, then you will need to edit gopigo_controller/src/gopigo_controller.py. Search for the gopigo_on flag and edit to transmit commands for your motors. You may need to edit the parameter values in gopigo_description/launch/gopigo_interface.launch

Installing Tutorial:

1- Create a new workspace called gopigo_ws using:

$ mkdir -p ~/catkin_ws/src

$ cd ~/catkin_ws/

$ catkin_make

2-Get the repository:

sudo git clone -b openloop https://github.com/richardw05/gopigo_ws.git

or

sudo git clone -b openloop https://github.com/richardw05/gopigo_ws.git

3-Build the repository by running:

$ catkin_make
