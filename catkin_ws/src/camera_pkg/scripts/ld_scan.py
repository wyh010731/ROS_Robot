#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from sensor_msgs.msg import LaserScan
import serial

# 串口初始化
ser = serial.Serial('/dev/ttyUSB1', 115200)

def laser_callback(data):
    # 获取激光雷达扫描数据
    ranges = data.ranges[0]
    ranges = int(round(ranges*100))

    # 将数据转换为字符串，并添加帧头
    msg = '@' + str(ranges) + '\n'

    # 将数据发送到串口
    ser.write(msg.encode())

    # 在终端上显示数据
    rospy.loginfo(ranges)

if __name__ == '__main__':
    # 初始化ROS节点
    rospy.init_node('laser_subscriber')

    # 订阅 /scan 主题
    rospy.Subscriber('/scan', LaserScan, laser_callback)

    # 循环等待回调函数
    rospy.spin()
