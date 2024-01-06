/*
    需求: 循环发布人的信息

*/

#include "ros/ros.h"
#include "object_detect/Person.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    //1.初始化 ROS 节点
    ros::init(argc,argv,"talker_person");

    //2.创建 ROS 句柄
    ros::NodeHandle nh;

    //3.创建发布者对象
    ros::Publisher pub = nh.advertise<object_detect::Person>("person_info",1000);

    //4.组织被发布的消息，编写发布逻辑并发布消息
    object_detect::Person p;
    p.detect_flag = 0;
    p.cx = 0;
    p.cy = 0;
    p.dx = 0;
    p.dy = 0;

    ros::Rate r(1);
    while (ros::ok())
    {
        pub.publish(p);
        p.cx += 1;
        ROS_INFO("%d %d %d %d %d",p.detect_flag, p.cx, p.cy, p.dx, p.dy);

        r.sleep();
        ros::spinOnce();
    }

    return 0;
}
