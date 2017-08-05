#!/usr/bin/env python


import rospy
import sys
from std_msgs.msg import String

def talker():
	
    pub = rospy.Publisher('chatter', String, queue_size=1000)
    period = int(sys.argv[1]) 
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(period) 
    prev_time = rospy.get_rostime()
    count = 0
    total_msg_sent = 0
    while ( (not rospy.is_shutdown()) and total_msg_sent < period*10):
        hello_str = "hello world %s" % rospy.get_time()
        now = rospy.get_rostime()
        diff_time = (now - prev_time).to_sec()
        count += 1
        total_msg_sent += 1
        if( diff_time >= 1.0):
			rospy.loginfo("{0}: {1} / {2} = {3}".format(total_msg_sent, count, diff_time, count/diff_time) )
			count=0
			prev_time = now
			
        pub.publish(hello_str)
        rate.sleep()

if __name__ == '__main__':
    try:
		if ( len(sys.argv) != 2 ):
			print 'First command line argument must be the publishing rate'
		else:	
			talker()
    except rospy.ROSInterruptException:
        pass
