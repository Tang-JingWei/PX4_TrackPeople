#include "object_track/object_track.hpp"

enum STEP
{
	PREPARE,	 // 准备
	TAKOFF_TASK, // 起飞任务
	OBJECT_TASK, // 目标检测跟踪任务
				 // TASK_FIRST,	 //任务1
				 // TASK_SECOND, //任务2
				 // TASK_THIRD,	 //任务3
				 // TASK_FOURTH, //任务4
				 // TASK_FIFTH,	 //任务5
				 // TASK_SIXTH,	 //任务6
} step_flow;

// 任务运行状态
bool step_state = true;
bool detect_state = false;
uint8_t detect_offline_cnt = 0;

// ROS实例
mavros_msgs::State current_state;		  // 订阅消息体类型的变量
geometry_msgs::PoseStamped high;		  // 订阅，主要获取无人机的z轴高度信息
mavros_msgs::PositionTarget velocity_msg; // 消息实例，
geometry_msgs::PoseStamped pose;
// 建立一个类型为SetMode的服务端offb_set_mode，并将其中的模式mode设为"OFFBOARD"，作用便是用于后面的
// 客户端与服务端之间的通信（服务）
mavros_msgs::SetMode offb_set_mode;
// 建立一个类型为CommandBool的服务端arm_cmd，并将其中的是否解锁设为"true"，作用便是用于后面的
// 客户端与服务端之间的通信（服务）
mavros_msgs::CommandBool arm_cmd;
mavros_msgs::RCIn rcin_channel;

data_t person_info; // 追踪人体信息


// 获得追踪的人物信息 回调函数
void doPerson(const object_detect::Person::ConstPtr& p){
	person_info.detect_flag = p->detect_flag;
	person_info.cx = p->cx;
	person_info.cy = p->cy;
	person_info.dx = p->dx;
	person_info.dy = p->dy;

	detect_state = true;
	detect_offline_cnt = 0;
}
// 订阅时的回调函数，接受到该消息体的内容时执行里面的内容，这里面的内容就是赋值
void state_cb(const mavros_msgs::State::ConstPtr &msg)
{
	current_state = *msg;
}
void high_fun(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
	high = *msg;
}
void rcin_fun(const mavros_msgs::RCInConstPtr msg)
{
	rcin_channel = *msg;
	if (rcin_channel.channels[6 - 1] >= 1500)
	{
		step_state = false;
	}
	else
	{
		step_state = true;
	}
}


void pose_control(double const x, double const y, double const z)
{
	pose.pose.position.x = x;
	pose.pose.position.y = y;
	pose.pose.position.z = z;
}
// body - xyz速度，偏航速度
void position_control_body_vxyzyawr(double const vx, double const vy, double const vz, float const yawr)
{
	velocity_msg.coordinate_frame = mavros_msgs::PositionTarget::FRAME_BODY_NED;
    velocity_msg.type_mask =    mavros_msgs::PositionTarget::IGNORE_PX | //Position ignore flags 位置
                                mavros_msgs::PositionTarget::IGNORE_PY |
                                mavros_msgs::PositionTarget::IGNORE_PZ | 
                                // mavros_msgs::PositionTarget::IGNORE_VX | //Velocity vector ignore flags 速度
                                // mavros_msgs::PositionTarget::IGNORE_VY |
                                // mavros_msgs::PositionTarget::IGNORE_VZ |
                                mavros_msgs::PositionTarget::IGNORE_AFX | //Acceleration/Force vector ignore flags 加速度
                                mavros_msgs::PositionTarget::IGNORE_AFY |
                                mavros_msgs::PositionTarget::IGNORE_AFZ |
                                mavros_msgs::PositionTarget::FORCE |
                                mavros_msgs::PositionTarget::IGNORE_YAW  //偏航
                                // mavros_msgs::PositionTarget::IGNORE_YAW_RATE; //偏航率
								;
	velocity_msg.velocity.x = vx;
	velocity_msg.velocity.y = vy;
	velocity_msg.velocity.z = 0;
	velocity_msg.yaw_rate = yawr;
	velocity_msg.header.stamp = ros::Time::now();
}
// body - xyz位置，偏航度
void position_control_body_xyzyawr(double const x, double const y, double const z, float const yawr)
{
	velocity_msg.coordinate_frame = mavros_msgs::PositionTarget::FRAME_BODY_NED;
	velocity_msg.type_mask = 0b011111111000;
	velocity_msg.position.x = x;
	velocity_msg.position.y = y;
	velocity_msg.position.z = z;
	velocity_msg.yaw_rate = yawr;
	velocity_msg.header.stamp = ros::Time::now();
}
// home - xyz位置，偏航度
void position_control_local_xyzyaw(double const x, double const y, double const z, float const yaw)
{
	velocity_msg.coordinate_frame = mavros_msgs::PositionTarget::FRAME_LOCAL_NED;
	velocity_msg.type_mask = 0b101111111000;
	velocity_msg.position.x = x;
	velocity_msg.position.y = y;
	velocity_msg.position.z = z;
	velocity_msg.yaw = yaw;
	velocity_msg.header.stamp = ros::Time::now();
}
// home - xyz位置，偏航速度
void position_control_local_xyzyawr(double const x, double const y, double const z, float const yawr)
{
	velocity_msg.coordinate_frame = mavros_msgs::PositionTarget::FRAME_LOCAL_NED;
	velocity_msg.type_mask = 0b011111111000;
	velocity_msg.position.x = x;
	velocity_msg.position.y = y;
	velocity_msg.position.z = z;
	velocity_msg.yaw_rate = yawr;
	velocity_msg.header.stamp = ros::Time::now();
}
// 速度、偏航角控制
void position_control_vxyz(double const vx, double const vy, float const yaw){
    velocity_msg.coordinate_frame = mavros_msgs::PositionTarget::FRAME_BODY_NED;
    velocity_msg.type_mask =    mavros_msgs::PositionTarget::IGNORE_PX | //Position ignore flags 位置
                                mavros_msgs::PositionTarget::IGNORE_PY |
                                mavros_msgs::PositionTarget::IGNORE_PZ | 
                                // mavros_msgs::PositionTarget::IGNORE_VX | //Velocity vector ignore flags 速度
                                // mavros_msgs::PositionTarget::IGNORE_VY |
                                // mavros_msgs::PositionTarget::IGNORE_VZ |
                                mavros_msgs::PositionTarget::IGNORE_AFX | //Acceleration/Force vector ignore flags 加速度
                                mavros_msgs::PositionTarget::IGNORE_AFY |
                                mavros_msgs::PositionTarget::IGNORE_AFZ |
                                mavros_msgs::PositionTarget::FORCE |
                                mavros_msgs::PositionTarget::IGNORE_YAW  //偏航
                                // mavros_msgs::PositionTarget::IGNORE_YAW_RATE //偏航率
                                ; 
    velocity_msg.velocity.x = vx;
    velocity_msg.velocity.y = vy;
    velocity_msg.velocity.z = 0;
    // velocity_msg.yaw = yaw;
    velocity_msg.yaw_rate = yaw;
    // velocity_msg.position.z = TAKOFF_HIGH;
    velocity_msg.header.stamp = ros::Time::now();
}



int main(int argc, char **argv)
{
	static uint8_t cnt; // 计数

	// data_t *person_info = (data_t *)(malloc(sizeof(data_t)));
	move_t *move = (move_t *)(malloc(sizeof(move_t)));
	// struct_init(person_info, moe);

	// ROS节点初始化
	ros::init(argc, argv, "object_track_main");

	// 创建节点句柄
	ros::NodeHandle nh;

	// 订阅发布者/服务客户端实例
	ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);
	ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
	ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming"); // 启动服务1
	ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");		// 启动服务2
	ros::Publisher local_position_pub = nh.advertise<mavros_msgs::PositionTarget>("mavros/setpoint_raw/local", 20);
	ros::Subscriber high_sub = nh.subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose", 10, high_fun);
	ros::Subscriber local_rc_in = nh.subscribe<mavros_msgs::RCIn>("/mavros/rc/in", 10, rcin_fun);
	ros::Subscriber sub = nh.subscribe<object_detect::Person>("person_info",10,doPerson);
	ros::Publisher vel_pub = nh.advertise<geometry_msgs::TwistStamped>("mavros/setpoint_velocity/cmd_vel", 10);

	// 设置循环的频率
	ros::Rate rate(20.0);

	// 等待飞控连接mavros，current_state是我们订阅的mavros的状态，连接成功在跳出循环
	ROS_INFO("fcu is connecting......");
	while (ros::ok() && !current_state.connected)
	{
		ros::spinOnce();
		rate.sleep();
	}
	ROS_INFO("fcu connected_ok!");

	// 首次发布位置，起飞
	//  pose_control(0, 0, TAKOFF_HIGH);
	//  local_pos_pub.publish(pose);

	offb_set_mode.request.custom_mode = "OFFBOARD"; // 模式切为 offboard
	arm_cmd.request.value = true;					// 解锁
	double home_high = high.pose.position.z;		// 起飞点高度记录

	ROS_INFO("home_high = %lf", home_high); // 打印输出当前高度

	// 更新时间
	ros::Time last_request = ros::Time::now();
	ros::Time step_time = ros::Time::now();

	// 当前任务步骤标志 
	// 不能设置成PREPARE
	// 因为在离板模式下要以>2hz的频率发送设置点消息
	// 而PREPARE状态中且解锁过程中不会有任何动作，故会退出
	int uav_task_stat = TAKOFF_TASK; 

	while (ros::ok())
	{
		// 1、设置模式和解锁
		// 首先判断当前模式是否为offboard模式，如果不是，则客户端set_mode_client向服务端offb_set_mode发起请求call，
		// 然后服务端回应response将模式返回，这就打开了offboard模式
		if (current_state.mode != "OFFBOARD" && (ros::Time::now() - last_request > ros::Duration(5.0)))
		{
			if (set_mode_client.call(offb_set_mode) && offb_set_mode.response.mode_sent)
			{
				ROS_INFO("Offboard enabled"); // 打开模式后打印信息
			}
			last_request = ros::Time::now();
		}
		else // else指已经为offboard模式，然后进去判断是否解锁，如果没有解锁，则客户端arming_client向服务端arm_cmd发起请求call
			 // 然后服务端回应response成功解锁，这就解锁了
		{
			if (!current_state.armed && (ros::Time::now() - last_request > ros::Duration(5.0)))
			{
				if (arming_client.call(arm_cmd) && arm_cmd.response.success)
				{
					ROS_INFO("Vehicle armed"); // 解锁后打印信息
				}
				last_request = ros::Time::now();
				step_time = ros::Time::now();
				uav_task_stat = TAKOFF_TASK; // 解锁后，初始任务为起飞
			}
		}

		// 2、在非<TAKOFF_TASK>状态下，保持飞行高度
		// if ((high.pose.position.z - home_high <= TAKOFF_HIGH - 0.5 || high.pose.position.z - home_high >= TAKOFF_HIGH + 0.5) && uav_task_stat != TAKOFF_TASK)
		// {
		// 	position_control_local_xyzyawr(
		// 		high.pose.position.x,	 // X位置
		// 		high.pose.position.y,	 // Y位置
		// 		TAKOFF_HIGH + home_high, // Z位置
		// 		0						 // YAW速度
		// 	);
		// 	local_position_pub.publish(velocity_msg); // 发布位置消息

		// 	// printf("Keep <TAKOFF_HIGH>......(保持高度)\n");

		// 	ros::spinOnce();
		// 	rate.sleep();
		// 	continue;
		// }

		// 2、任务的执行
		switch (uav_task_stat)
		{

		case PREPARE:
		//
		break;

		case TAKOFF_TASK: // 起飞任务
		{
			if ((high.pose.position.z - home_high <= TAKOFF_HIGH - 0.5) || (high.pose.position.z - home_high >= TAKOFF_HIGH + 0.5))
			{
				position_control_local_xyzyawr(
					0,						 // X位置
					0,						 // Y位置
					TAKOFF_HIGH + home_high, // Z位置
					0						 // YAW速度
				);
				local_position_pub.publish(velocity_msg); // 发布位置消息

				// printf("Flying to <TAKOFF_HIGH>......(正在飞向预设高度)\n");

			}
			else
			{
				cnt++;

				if (cnt == 20)
				{
					uav_task_stat = OBJECT_TASK; // 切换至追踪任务
					ROS_INFO("Change TO <OBJECT_TASK> !!!");

					cnt = 0;
				}
			}
		}
		break;

		case OBJECT_TASK: // 目标识别跟踪任务
		{
			if (1 == person_info.detect_flag && detect_state) //识别到目标
			{
				ROS_INFO("追踪到的人体信息: %d, %d, %d, %d, %d\n", person_info.detect_flag, person_info.cx, person_info.cy, person_info.dx, person_info.dy);
				ROS_INFO("[速度控制] [x]:%lf   [yaw]:%lf\n", move->x_vel, move->yawr);

				PID_Calculation(move, &person_info); // PID计算

				position_control_body_vxyzyawr(
						move->x_vel, // X的速度
						move->y_vel, // Y的速度
						move->z_vel, // Z的速度
						move->yawr   // YAW的速度
					);
					// position_control_vxyz(
						// move->x_vel, // X的速度
						// move->y_vel, // Y的速度
						// move->z_vel, // Z的速度
						// move->yawr   // YAW的速度
						// );
				local_position_pub.publish(velocity_msg);
			}
			else
			{
				if (!detect_state)
				{
					ROS_INFO("YOLOV5掉线...");
				}
				
				position_control_body_vxyzyawr(
						0, // X的速度
						0, // Y的速度
						0, // Z的速度
						0   // YAW的速度
					);
					// position_control_vxyz(
						// 0, // X的速度
						// 0, // Y的速度
						// 0   // YAW的速度
						// );
				local_position_pub.publish(velocity_msg);
			}
		}
		break;

		}

		// TODO:断线检测
		// 终止程序逻辑 --> 6通道打开，强制退出程序
		if (!step_state)
		{
			printf("Program Control EXIT !!!\n");
			return 0;
		}

		// 断线检测
		detect_offline_cnt++;
		if (detect_offline_cnt >= 10)
		{
			detect_state = false;
			// detect_offline_cnt = 0;
		}
		


		// 执行回调更新数据，按照循环频率延时
		ros::spinOnce();
		rate.sleep();
	}

	return 0;
}
