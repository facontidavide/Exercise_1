#!/usr/bin/env python

import rospy
from std_msgs.msg import String

class Listener():
    def __init__(self):
		rospy.init_node('listener', anonymous=True)
		rospy.Subscriber('chatter', String, self.callback)
		self.count = 0
		self.total_msg_count = 0
		self.prev_time = rospy.get_rostime()

    def callback(self,data):
		now = rospy.get_rostime()
		diff_time = (now - self.prev_time).to_sec()
		self.count += 1
		self.total_msg_count += 1
		if( diff_time >= 1.0):
			rospy.loginfo("{0}: {1} / {2} = {3}".format(self.total_msg_count, self.count, diff_time, self.count/diff_time) )
			self.count = 0
			self.prev_time = now

if __name__ == '__main__':
	listener = Listener()
	rospy.spin()
