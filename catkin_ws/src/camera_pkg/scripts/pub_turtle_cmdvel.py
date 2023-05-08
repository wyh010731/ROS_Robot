#!/usr/bin/env python 
# coding=utf-8
#1.编译器声明和2.编码格式声明
#1:为了防止用户没有将python安装在默认的/usr/bin目录，系统会先从env(系统环境变量)里查找python的安装路径，再调用对应路径下的解析器完成操作，也可以指定python3
#2:Python.X 源码文件默认使用utf-8编码，可以正常解析中文，一般而言，都会声明为utf-8编码

import rospy #引用ROS的Python接口功能包
import numpy as np #引用数组功能包
from geometry_msgs.msg import Twist #引用ROS的速度消息格式


#定义一个图片转换的类，功能为：订阅ROS图片消息并转换为OpenCV格式处理，处理完成再转换回ROS图片消息后发布
class Line_Follow:
 def __init__(self): #类成员初始化函数   
     self.cmd_vel_pub = rospy.Publisher("turtle1/cmd_vel", Twist, queue_size=1) #初始化发布者,发表话题名为“cmd_vel”,该名与其它节点订阅的控制命令话题要求一致，消息格式为Twist也其它节点订阅的控制命令话题消息格式要求一致
     self.twist = Twist() #创建速度控制命令变量

if __name__ == '__main__': #这段判断的作用是，如果本py文件是直接运行的则判断通过执行if内的内容，如果是import到其他的py文件中被调用(模块重用)则判断不通过
  self.twist.linear.x  = 0.5 #没有识别到直线则发布控制速度0，小车停止
  self.twist.angular.z = 1.0
  while(1):
      self.cmd_vel_pub.publish(self.twist)

