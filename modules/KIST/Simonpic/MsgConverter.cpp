#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include "../../json/json.h"
#include "../../jsoncpp.cpp"

// Include SimonPiC msg type
#include <simonpic_msgs/MultiPersons.h>
#include <simonpic_msgs/Person.h>

std::string json_str;

void MsgConverter(std_msgs::String& jsonEncodedResult_Output, const simonpic_msgs::MultiPersons::ConstPtr& simonpic_msg){

//	##########################<Input>#########################
//	# SimonPiC msg (Multipersons)
//	##########################<Output>########################
//	# jsonEncodedResult_Output : json format output
//	# 1. Id
//	# 2. Name
//	# 3. Age
//	# 4. Location 	<-- from SimonPiC msg
//	# 5. Social context 
//	##########################################################


	////////////////////////////////////////////////////////
	// Example
	////////////////////////////////////////////////////////

	// Convert float to string
	std::string x,y,z;
	std::ostringstream buff_x, buff_y, buff_z;

	buff_x << simonpic_msg->persons[0].location.x ;
	x = buff_x.str();
	buff_y << simonpic_msg->persons[0].location.y ;
	y = buff_y.str();
	buff_z << simonpic_msg->persons[0].location.z ;
	z = buff_z.str();


	// Create json
	Json::Value root;

	// 1. Info
	Json::Value info;
	info["MODULE"] = "KIST_simonpic";
	info["start"] = 500;
	info["end"] = 700;
	root["1.INFO"] = info;

	// 2. Human Info
	Json::Value human_info;
	human_info["Id"] = 1;
	human_info["Name"] = "KJH";
	human_info["Age"] = 20;
	human_info["X position"] = x;	// <-- put x,y,z from simonpic msg
	human_info["Y position"] = y;
	human_info["Z position"] = z;
	root["2.Human_Info"] = human_info;

	// 3. Social Context
	Json::Value social_context;
	social_context["Id"] = 1;
	social_context["Tag"] = "Emotion";
	social_context["Keyword"] = "Happy";
	root["3.Social_CONTEXT"] = social_context;	

	Json::StyledWriter writer;
	json_str = writer.write(root);
//	std::cout << json_str << std::endl << std::endl;

	// convert json to String form
	std_msgs::String msg;
	msg.data = json_str.c_str();

	
//	std::cout << msg << std::endl << std::endl;

	jsonEncodedResult_Output.data = msg.data;

}
