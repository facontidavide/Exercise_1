
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
	if( argc != 2)
	{
		std::cout<< "Expecting the publishing rate as first command line argument" << std::endl;
		return 1;
	}	
	const int PERIOD = atoi(argv[1]);

  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 10);
  ros::Rate loop_rate(PERIOD);

  int count = 0;
  ros::Time prev_time = ros::Time::now();
  
  while (ros::ok())
  {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();


	ros::Time curr_time = ros::Time::now();
	double diff_time = (curr_time - prev_time).toSec();
	count++;
	
  	if( diff_time >= 1.0)
  	{
		ROS_INFO("%f / %f = %f", (double)count, diff_time , count/diff_time);
		count = 0;
		prev_time = curr_time;
	}

    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();

  }


  return 0;
}

