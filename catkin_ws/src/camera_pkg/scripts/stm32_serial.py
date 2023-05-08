#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan
import serial
import time

port = '/dev/ttyUSB1'  # STM32端口
baudrate = 115200  # 波特率
header = '@'  # 数据帧头

ser = None  # 串口对象

def cmd_vel_callback(msg):
    global ser
    try:
        v_l = int(msg.linear.x * 1000)  # 将线速度转化为脉冲速度
        v_r = int(msg.angular.z * 1000)  # 将角速度转化为脉冲速度
        cmd = "{header}{v_l:04d}{v_r:04d}\r\n".format(header=header, v_l=v_l, v_r=v_r)  # 将脉冲速度转化为4位十进制数，并添加数据帧头
        ser.write(cmd.encode('ascii'))  # 将命令转化为ascii码发送
        rospy.loginfo("Send cmd_vel: v_l=%d, v_r=%d", v_l, v_r)
    except Exception as e:
        rospy.logwarn("Send cmd_vel failed: %s", str(e))

def laser_callback(data):
    global ser
    try:
        # 获取激光雷达扫描数据
        ranges = data.ranges[0]
        ranges = int(round(ranges*100))
        # 将数据转换为字符串，并添加帧头
        msg = "#{:08d}".format(ranges)  # 将激光雷达数据转化为8位十进制数，并添加帧头
        # 将数据发送到串口
        ser.write(msg.encode())
        # 在终端上显示数据
        rospy.loginfo(ranges)
    except Exception as e:
        rospy.logwarn("Send laser data failed: %s", str(e))

def main():
    global ser
    rospy.init_node('stm32_serial')
    rospy.loginfo("Starting STM32 serial node...")
    # 初始化串口
    try:
        ser = serial.Serial(port=port, baudrate=baudrate)
        rospy.loginfo("Serial port initialized: %s", port)
    except Exception as e:
        rospy.logerr("Serial port init failed: %s", str(e))
        return

    # 订阅/cmd_vel消息
    rospy.Subscriber("/cmd_vel", Twist, cmd_vel_callback)
    
    # 订阅/scan消息
    rospy.Subscriber('/scan', LaserScan, laser_callback)

    # 循环执行
    rate = rospy.Rate(10)  # 发送频率为10Hz
    while not rospy.is_shutdown():
        rate.sleep()

    # 关闭串口
    if ser:
        ser.close()

if __name__ == '__main__':
    main()
#   这个程序会同时订阅/cmd_vel和/scan两个话题，并将接收到的数据转化为字符串后发送到串口。
#   其中前8位为激光雷达数据，后8位为机器人运动