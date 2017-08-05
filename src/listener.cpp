
#include "ros/ros.h"
#include "std_msgs/String.h"

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
	static ros::Time prev_time = ros::Time::now();
	static int count = 0;
	
	ros::Time curr_time = ros::Time::now();
	double diff_time = (curr_time - prev_time).toSec();
	count++;
	
  	if( diff_time >= 1.0)
  	{
		ROS_INFO("%f / %f = %f", (double)count, diff_time , count/diff_time);
		count = 0;
		prev_time = curr_time;
	}
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 10, chatterCallback);
  ros::spin();


  return 0;
}

