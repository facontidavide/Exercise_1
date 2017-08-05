
#include "ros/ros.h"
#include "rate_test/SuperAwesome.h"


void chatterCallback(const rate_test::SuperAwesome::ConstPtr& msg)
{
	static ros::Time prev_time = ros::Time::now();
	static int count = 0;
	static int total_msg_count = 0;
	
	ros::Time curr_time = ros::Time::now();
	double diff_time = (curr_time - prev_time).toSec();
	count++;
	total_msg_count++;
	
	// show the rate once per second
  	if( diff_time >= 1.0)
  	{
		ROS_INFO("%d : %f / %f = %f",total_msg_count, (double)count, diff_time , count/diff_time);
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

