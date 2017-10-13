#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>


// Include SimonPiC msg type
#include <simonpic_msgs/MultiPersons.h>
#include <simonpic_msgs/Person.h>

// Include msg converter
#include "../modules/KIST/Simonpic/MsgConverter.cpp"


void Callback(const simonpic_msgs::MultiPersons::ConstPtr& simonpic_msg);
ros::Publisher pub;
ros::Subscriber sub;


int main(int argc, char **argv){

	// 1. ROS Node setting
	ros::init(argc, argv, "node_KistSimonpic");
	ros::NodeHandle n;

	// 2. ROS Subscriber setting
	sub = n.subscribe("/three_w/three_w", 100, Callback);


	// 3. ROS Publisher setting
 	pub = n.advertise<std_msgs::String>("json_RecogRes", 100);

	ros::spin();

	return 0;
}


void Callback(const simonpic_msgs::MultiPersons::ConstPtr& simonpic_msg){


	std_msgs::String jsonEncodedResult_Output;

	// 1. Perform MsgConverter (SimonPiC msg --> Json format msg)
//	printf("# of Detected person : %d \n", simonpic_msg->total);
//	std::cout << simonpic_msg->total	<< std::endl;;
	if (simonpic_msg->total != 0)
		MsgConverter(jsonEncodedResult_Output,simonpic_msg);

	// 2. Publish the json format string
	if (!jsonEncodedResult_Output.data.empty())
	{
//		std::cout << jsonEncodedResult_Output << std::endl << std::endl ;
		pub.publish(jsonEncodedResult_Output);
	}


}



