/*
    需求: 订阅人的信息

*/

#include "ros/ros.h"
#include "object_detect/Person.h"

void doPerson(const object_detect::Person::ConstPtr& p){
    ROS_INFO("订阅的人信息:%d, %d, %d, %d, %d", p->detect_flag, p->cx, p->cy, p->dx, p->dy);
}

int main(int argc, char *argv[])
{   
    setlocale(LC_ALL,"");

    //1.初始化 ROS 节点
    ros::init(argc,argv,"listener_person");
    //2.创建 ROS 句柄
    ros::NodeHandle nh;
    //3.创建订阅对象
    ros::Subscriber sub = nh.subscribe<object_detect::Person>("person_info",10,doPerson);

    //4.回调函数中处理 person

    //5.ros::spin();
    ros::spin();    
    return 0;
}
