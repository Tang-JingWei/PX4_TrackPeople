#ifndef _OBJECT_TRACK_FUN_
#define _OBJECT_TRACK_FUN_

#include "object_track/object_track.hpp"

/*
    相关参数初始化
*/
int struct_init(data_t* person_info, move_t* move){
    
    // person_info的初始化，假设刚开始的目标点在图像中心，防止一开始就误运动
	person_info->detect_flag = 0;
	person_info->cx = 0.5;
	person_info->cy = 0.5;
	person_info->dx = 0.1;
	person_info->dy = 0.2;

    //初始化move
    move->x_vel = 0;
    move->y_vel = 0;
    move->z_vel = 0;
    move->yawr = 0;

    return 0;
}


/*
    PID算出速度
*/
void PID_Calculation(move_t *move, data_t *const data)
{
    double k = 50; // 中心%50

    // 控制X速度逻辑
    if (data->cy - k > -Y_OVERLOOK_K && data->cy - k < Y_OVERLOOK_K) //目标在图像中心一定范围内，无动作
    { 
        move->x_vel = 0;
    }
    else if (data->cy - k > Y_OVERLOOK_K)//目标在图像中心的下方，后退
    { 
        move->x_vel = -(fabs(data->cy - k) * 0.01);
    }
    else if (data->cy - k < -Y_OVERLOOK_K)//目标在图像中心的上方，前进
    { 
        move->x_vel = fabs(data->cy - k) * 0.01;
    }

    // 控制yaw速度逻辑
    if (data->cx - k > -X_OVERLOOK_K && data->cx - k < X_OVERLOOK_K) //目标在图像中心的一定范围内，无动作
    { 
        move->yawr = 0.0;
    }
    else if (data->cx - k > X_OVERLOOK_K) //目标在图像中心的右边，顺序针偏航
    {
        move->yawr = -0.25;
        // move->yawr = -((data->cx - k)*5+1);
    }
    else if (data->cx - k < -X_OVERLOOK_K) //目标在图像中心的左边，逆时针偏航
    { 
        move->yawr = 0.25;
        // move->yawr = (data->cx - k)*5+1;
    }
}


int data_disposal(move_t *move, data_t *const data)
{
    double img_tall = 480;                                                                   //图像高
    double img_wide = 640;                                                                   //图像宽
    double vide_angle = 120 * ANGTORAD_COE;                                                  //相机视野角，弧度
    double camera_ground_level_angle = 30 * ANGTORAD_COE;                                    //相机与地面的水平角，弧度
    double nva_ground_tall = 0.0;                                                            //无人机离地面的高度
    double img_tall_ang = img_tall * vide_angle / sqrt(pow(img_tall, 2) + pow(img_wide, 2)); //图像高度的视野角
    double img_wide_ang = img_wide * vide_angle / sqrt(pow(img_tall, 2) + pow(img_wide, 2)); //图像宽度的视野角

    //初始化move
    move->x_vel = 0;
    move->y_vel = 0;
    move->z_vel = 0;
    move->yawr = 0;

    double k = 0.5;
    if (data->cy - k > -Y_OVERLOOK_K && data->cy - k < Y_OVERLOOK_K)
    { //目标在图像中心一定范围内，无动作
        move->x_vel = 0;
    }
    else if (data->cy - k > Y_OVERLOOK_K)
    { //目标在图像中心的下方，后退
        move->x_vel = -(fabs(data->cy - k)*5+1);
        // move->x_vel = -1;
    }
    else if (data->cy - k < -Y_OVERLOOK_K)
    { //目标在图像中心的上方，前进
        move->x_vel = fabs(data->cy - k)*5+1;
        // move->x_vel = 1;
    }
    if (data->cx - k > -X_OVERLOOK_K && data->cx - k < X_OVERLOOK_K)
    { //目标在图像中心的一定范围内，无动作
        move->yawr = 0.0;
    }
    else if (data->cx - k > X_OVERLOOK_K)
    { //目标在图像中心的右边，顺序针偏航
        move->yawr = -0.25;
        // move->yawr = -((data->cx - k)*5+1);
    }
    else if (data->cx - k < -X_OVERLOOK_K)
    { //目标在图像中心的左边，逆时针偏航
        move->yawr = 0.25;
        // move->yawr = (data->cx - k)*5+1;
    }
    // printf("xv: %lf\tyaw: %lf\n", move->x_vel, move->yaw);
    return 0;
}



#endif