#! /usr/bin/env python
"""
    需求: 实现基本的话题通信，一方发布数据，一方接收数据，
         实现的关键点:
         1.发送方
         2.接收方
         3.数据(此处为普通文本)

         PS: 二者需要设置相同的话题


    消息发布方:
        循环发布信息:HelloWorld 后缀数字编号

    实现流程:
        1.导包 
        2.初始化 ROS 节点:命名(唯一)
        3.实例化 发布者 对象
        4.组织被发布的数据，并编写逻辑发布数据


"""
#1.导包 
import rospy
from fly.msg import track

if __name__ == "__main__":
    #2.初始化 ROS 节点:命名(唯一)
    rospy.init_node("talker_p")
    #3.实例化 发布者 对象
    pub = rospy.Publisher("track_person",track,queue_size=5)
    #4.组织被发布的数据，并编写逻辑发布数据
    t = track()  #创建 msg 对象
    t.track_flag = 1
    t.track_cx = 55
    t.track_cy = 45
    count = 0  #计数器 
    # 设置循环频率
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        pub.publish(t)
        rate.sleep()
        rospy.loginfo("检测数据: %d %d %d",t.track_flag,t.track_cx,t.track_cy)
