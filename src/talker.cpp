
#include "ros/ros.h"
#include "rate_test/SuperAwesome.h"
#include <sstream>


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
  

  ros::Publisher chatter_pub = n.advertise<rate_test::SuperAwesome>("chatter", 1000);
  ros::Rate loop_rate(PERIOD);

  int count = 0;
  int total_msg_count = 0;
  ros::Time prev_time = ros::Time::now();
  
   
  while (ros::ok() && total_msg_count < PERIOD*10)
  {
    rate_test::SuperAwesome msg;
    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

	ros::Time curr_time = ros::Time::now();
	double diff_time = (curr_time - prev_time).toSec();
	count++;
	total_msg_count++;
	
	// show the rate once per second
  	if( diff_time >= 1.0)
  	{
		ROS_INFO("%d: %f / %f = %f", total_msg_count, (double)count, diff_time , count/diff_time);
		count = 0;
		prev_time = curr_time;
	}

    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  } 

  ROS_INFO("total_messages: %d", total_msg_count);

  return 0;
}

