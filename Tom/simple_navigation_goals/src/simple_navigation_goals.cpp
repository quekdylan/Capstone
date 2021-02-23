#include <ros/ros.h>
#include "std_msgs/String.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void commandsCallback(const std_msgs::String::ConstPtr& msg)
{
	//tell the action client that we want to spin a thread by default
  	MoveBaseClient ac("move_base", true);

	//wait for the action server to come up
	while (!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}

  	move_base_msgs::MoveBaseGoal goal;
	
	std_msgs::String msgCheckStop;

	std::stringstream ssStop;
	ssStop << "emergency_stop";
	msgCheckStop.data = ssStop.str();


	std_msgs::String msgCheckStation;

	std::stringstream ssStation;
	ssStation << "return_home";
	msgCheckStation.data = ssStation.str();

	if (msg->data.c_str() == msgCheckStop.data)
	{
		//ros::topic::waitForMessage("amcl_pose");
	}

	else if (msg->data.c_str() == msgCheckStation.data)
	{
		//we'll send a goal to the robot
		goal.target_pose.header.frame_id = "odom";
		goal.target_pose.header.stamp = ros::Time::now();

		goal.target_pose.pose.position.x = -0.271257400513;
		goal.target_pose.pose.position.y = 2.55987668037;

		goal.target_pose.pose.orientation.z = 0.572060112472;
		goal.target_pose.pose.orientation.w = 0.820211696892;

		ROS_INFO("Sending goal");
		ac.sendGoal(goal);
	}

	ROS_INFO(msg->data.c_str());
	return;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //receive command from website
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("commands", 1000, commandsCallback);
  ros::spin();

  return 0;
}


