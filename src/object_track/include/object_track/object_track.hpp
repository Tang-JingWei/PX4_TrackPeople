#ifndef _OBJECT_TRACK_
#define _OBJECT_TRACK_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>	//文件读写
#include <dirent.h>
#include <string.h> //字符串操作
#include <sys/stat.h>
#include <sys/types.h>
#include <ros/ros.h>
#include "ros/service.h"

#include <geometry_msgs/PoseStamped.h>  //发布的消息体对应的头文件，该消息体的类型为geometry_msgs：：PoseStamped
#include <mavros_msgs/CommandBool.h>  //CommandBool服务的头文件，该服务的类型为mavros_msgs：：CommandBool
#include <mavros_msgs/SetMode.h>     //SetMode服务的头文件，该服务的类型为mavros_msgs：：SetMode
#include <mavros_msgs/State.h>  //订阅的消息体的头文件，该消息体的类型为mavros_msgs：：State
#include <mavros_msgs/PositionTarget.h> //发布消息，来控制无人机的运动
#include <geometry_msgs/PoseStamped.h> //用来订阅无人机的位置信息，相对home点
#include <mavros_msgs/RCIn.h> //订阅遥控器输入信息，主要用来使用6通道，退出程序运行
#include <geometry_msgs/TwistStamped.h>
#include "object_detect/Person.h"

#define PI 3.1415926535898
#define ANGTORAD_COE (PI/180)
#define RADTOANG_COE (180/PI)
#define Y_OVERLOOK_K 10 //图像中心点y坐标无动作范围	
#define X_OVERLOOK_K 12 //图像中心点x坐标无动作范围
						  //即锁定的目标在图像中心左右范围内，程序无动作，即无人机无动作
#define LANGUAGE ZH //设置信息输出的语言：EH/ZH
#define TIME_DIST 0.25 //目标在图像内可允许移动的最大距离，即本次帧与上一帧俩锁定目标之间可允许的最大距离
#define YOLO_RUNS_DETECT_PATH "/home/nuc11/workspace/yolov5/runs/detect/" //Yolov5的检测的保存路径，到detect/目录， exp的不写
#define PRINTF_SWITCH //打印输出开关

//起飞高度，飞行高度
#define TAKOFF_HIGH 3 

//存放读取到的数据结构体
typedef struct dataest
{
	uint8_t detect_flag;
	uint8_t cx; //目标中心点相对左上角 x 坐标值
	uint8_t cy; //目标中心点相对左上角 y 坐标值
	uint8_t dx;	//目标的宽度
	uint8_t dy;	//目标的高度
} data_t;

typedef struct moveest
{
	double x_vel; //无人机前进速度
	double y_vel;
	double z_vel; //对应无人机的高度，
	double yawr;	  //对应 data 的 x_point, 无人机航向角，及偏航
} move_t;

//数据初始化
extern int struct_init(data_t* person_info, move_t* move);
// PID计算
void PID_Calculation(move_t *move, data_t *const data);

//订阅mavros_msgs::State消息，回调函数
extern void state_cb(const mavros_msgs::State::ConstPtr& msg);
//订阅geometry_msgs::PoseStamped消息，回调函数
extern void high_fun(const geometry_msgs::PoseStamped::ConstPtr& msg);
//位置控制
extern void pose_control(double const x, double const y, double const z);
// 速度、偏航角控制
extern void position_control_xyz(double const vx, double const vy, float const yaw);



#endif