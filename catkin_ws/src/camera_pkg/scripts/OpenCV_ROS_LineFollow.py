#!/usr/bin/env python 
# coding=utf-8
#1.编译器声明和2.编码格式声明
#1:为了防止用户没有将python安装在默认的/usr/bin目录，系统会先从env(系统环境变量)里查找python的安装路径，再调用对应路径下的解析器完成操作，也可以指定python3
#2:Python.X 源码文件默认使用utf-8编码，可以正常解析中文，一般而言，都会声明为utf-8编码

import rospy #引用ROS的Python接口功能包
import cv2, cv_bridge #引用opencv功能包。cv_bridge是ROS图像消息和OpenCV图像之间转换的功能包
import numpy as np #引用数组功能包
from sensor_msgs.msg import Image #引用ROS内的图片消息格式
from geometry_msgs.msg import Twist #引用ROS的速度消息格式

'''
#调阈值回调函数
def Thresholdcallback(object):
    pass

#创建画布、窗口、进度条
canvas = np.zeros((170, 600, 3), dtype=np.uint8) + 255 #创建画布放置阈值动态调节窗口
cv2.imshow("THRESHOLD",canvas)
cv2.createTrackbar("R_min","THRESHOLD",0,255,Thresholdcallback) #输入参数(参数名字，进度条附着窗口名字，进度条最小值，进度条最大值，回调函数)
cv2.createTrackbar("R_max","THRESHOLD",0,255,Thresholdcallback)  
cv2.createTrackbar("G_min","THRESHOLD",0,255,Thresholdcallback)
cv2.createTrackbar("G_max","THRESHOLD",0,255,Thresholdcallback)
cv2.createTrackbar("B_min","THRESHOLD",0,255,Thresholdcallback)
cv2.createTrackbar("B_max","THRESHOLD",0,255,Thresholdcallback)
cv2.createTrackbar("kernel_width","THRESHOLD",1,20,Thresholdcallback)
cv2.createTrackbar("kernel_height","THRESHOLD",1,20,Thresholdcallback)'''
#动态调节窗口在调试完成得到合适的阈值参数后应该注释掉，以节省系统资源

#定义一个图片转换的类，功能为：订阅ROS图片消息并转换为OpenCV格式处理，处理完成再转换回ROS图片消息后发布
class Line_Follow:
 def __init__(self): #类成员初始化函数   
     self.bridge = cv_bridge.CvBridge() #初始化图片转换功能，cv_bridge.CvBridge()
     self.image_sub = rospy.Subscriber("/camera/rgb/image_raw", Image, self.callback) #初始化订阅者,rospy.Publisher()功能是创建订阅者类并输出
     self.cmd_vel_pub = rospy.Publisher("cmd_vel", Twist, queue_size=1) #初始化发布者,发表话题名为“cmd_vel”,该名与其它节点订阅的控制命令话题要求一致，消息格式为Twist也其它节点订阅的控制命令话题消息格式要求一致
     self.twist = Twist() #创建速度控制命令变量

 def callback(self, data): #订阅者接受到消息后的回调函数
     cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8") #ROS图片消息转换为OpenCV图片格式
     cv_image = cv2.resize(cv_image, (320,240), interpolation=cv2.INTER_AREA) #压缩图片，降低图片分辨率为320*240。这一段很重要，分辨率太高会导致图像处理需要的算力大增，降低实时性，从而降低巡线效果
     (rows, cols, channels) = cv_image.shape #获得转换后图片的宽度、高度和图片通道数

     #进度条值赋值相关变量
     '''R_min = cv2.getTrackbarPos("R_min","THRESHOLD",) #获得进度条值
     G_min = cv2.getTrackbarPos("G_min","THRESHOLD",)
     B_min = cv2.getTrackbarPos("B_min","THRESHOLD",)
     R_max = cv2.getTrackbarPos("R_max","THRESHOLD",)
     G_max = cv2.getTrackbarPos("G_max","THRESHOLD",)
     B_max = cv2.getTrackbarPos("B_max","THRESHOLD",)
     kernel_width=cv2.getTrackbarPos("kernel_width","THRESHOLD",)
     kernel_height=cv2.getTrackbarPos("kernel_height","THRESHOLD",)
     if(kernel_width<1):kernel_width=1
     if(kernel_height<1):kernel_height=1'''
     #动态调节窗口在调试完成得到合适的阈值参数后应该注释掉，以节省系统资源

     #使用数组进行彩色图像二值化
     #lower_yellow = np.array([B_min, G_min, R_min])
     #upper_yellow = np.array([B_max, G_max, R_max])
     hsv_image = cv2.cvtColor(cv_image, cv2.COLOR_RGB2HSV)  #将RGB图像转换为HSV图像
     lower_white = np.array([0, 0, 180])  # 调试得到的合适的阈值，白色
     upper_white = np.array([255, 30, 255])  # 调试得到的合适的阈值，白色
     yellow_mask = cv2.inRange(hsv_image, lower_white, upper_white)  # 过滤掉非黄色的部分

     kernel_width = 5
     kernel_height = 5
     kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (kernel_width, kernel_height))
     image_threshold = cv2.erode(yellow_mask, kernel)
     image_threshold = cv2.dilate(image_threshold, kernel)
     image_threshold = cv2.dilate(image_threshold, kernel)
     image_threshold = cv2.erode(image_threshold, kernel)

     #使用OpenCV的API进行霍夫变换直线识别    
     Rho=1 #生成极坐标时的像素扫描步长
     Theta=np.pi/90 #生成极坐标时的角度步长
     CurveNumber=100 #极坐标交点上的曲线最低数量要求
     minLineLength = 100 #长度低于100像素点的直线被忽略
     maxLineGap = 10 #距离大于10像素点的点被认为在两条不同的直线上
     lines = cv2.HoughLinesP(image_threshold, Rho, Theta, CurveNumber, minLineLength, maxLineGap)

     
     logest_line=0
     logest_lenghth=0
     try:
      #在识别出来的多条直线中进行比较，获得长度最长的直线
      logest_line=lines[0]
      for line in lines:
       for x1,y1,x2,y2 in line:
        lenghth=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)
       for x1,y1,x2,y2 in logest_line:
        logest_lenghth=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)
       if lenghth>=logest_lenghth:
        logest_line=line
      print("Line detected.") 
      print("Longes line's length is "+str(logest_lenghth**0.5)) #打印最长直线的长度

      #判断最长直线在画面中是偏左还是偏右
      for x1,y1,x2,y2 in logest_line:
         cv2.line(cv_image, (x1,y1), (x2,y2), (255,0,0), 2) #把最长直线在画面中标示出来           
         X=int((x1+x2)/2)-25 #求直线中点坐标，用于判断直线偏移方向与程度。25是摄像头位置补偿参数，我们目前使用摄像头是双目摄像头，而RGB摄像头位于右方，不是位于正中间
         Y=int((y1+y2)/2) 
         cv2.circle(cv_image, (X, Y), 75, (0, 0, 255), 5)#在原图画圆，把直线中点标示出来
         cv2.putText(cv_image,str(X),#把直线中点坐标用文字显示出来
                     (X-15, Y),#字体坐标
                     cv2.FONT_HERSHEY_SIMPLEX,
                     1,#字体大小
                     (0, 255, 0),#字体颜色BGR
                     3)
           
         #求最长直线偏移程度，并根据偏移程度发布速度控制命令
         Turn_error=cols/2-X #直线偏左为正，偏右为负
         if Turn_error<35 and Turn_error>-35: #直线在中心一定范围内可以认为没有偏移
            Turn_error=0
         self.twist.linear.x  = 0.2 #速度控制命令的前进速度大小0.2m/s
         self.twist.angular.z = Turn_error*0.0016 #速度控制命令的转向速度大小取决于直线偏移程度，左转为正，右转为负        
     except TypeError or UnboundLocalError: 
               print("No line detected.")
               self.twist.linear.x  = 0 #没有识别到直线则发布控制速度0，小车停止
               self.twist.angular.z = 0
             
     #发布控制命令
     self.cmd_vel_pub.publish(self.twist)

     #直接使用OpenCV创建窗口显示图片
     cv2.imshow("cv_image", cv_image) #OpenCV创建窗口显示原图
     cv2.imshow("image_threshold", image_threshold) #OpenCV创建窗口显示最终处理图片
     #cv2.imshow("THRESHOLD",canvas) #显示动态调参窗口
     cv2.waitKey(1) #功能为刷新图像，若要创建窗口显示图片必须有这一函数。入口参数为延时时间，单位ms，为0则无限延时。函数返回延时时间内键盘按键的ASCII码值

if __name__ == '__main__': #这段判断的作用是，如果本py文件是直接运行的则判断通过执行if内的内容，如果是import到其他的py文件中被调用(模块重用)则判断不通过
  rospy.init_node("OpenCVLineFollow") #创建节点
  rospy.loginfo("OpenCVLineFollow node started") #打印ROS消息说明节点已开始运行
  Line_Follow() #直接运行image_converter()函数创建类，该类在运行期间会一直存在。因为该类没有需要调用的函数，所以使用赋值的形式：a=image_converter()
  rospy.spin() #相当于while(1),当订阅者接收到新消息时调用回调函数

