# PX4_TrackPeople

## 相关说明

- 本项目技术栈：Linux、ROS、Yolov5、C/C++

## Yolov5

- Yolov5官方代码：https://github.com/ultralytics/yolov5
- Yolov5开箱即用开源项目：https://github.com/Tang-JingWei/EasyRun-jetson-nano-yolov5

## 目录说明

### `object_detect` 目录

- 目标识别任务
  - Yolov5仓库源码

### `object_track` 目录

- `object_track_fun.cpp` 功能函数
- `object_track_node.cpp` 追踪主任务

## 项目的使用

### 仿真

- 开启四个终端，分别执行以下四个命令

- 启动gazebo
  ```bash
  make px4_sitl_default gazebo
  ```

- 机载电脑与PX飞控建立连接

  ```bash
  roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14557"
  ```

- 运行 `object_track_node` 节点
  ```bash
  source ./devel/setup.zsh
  ```

  ```bash
  rosrun object_track object_track_node
  ```

- 运行 `my_detect` 节点
  ```bash
  source ./devel/setup.zsh
  ```

  ```bash
  rosrun object_detect my_detect.py
  ```

### 真机

- 机载电脑与PX飞控建立连接

  ```bash	
  roslaunch mavros px4.launch
  ```

- 运行 `object_track_node` 节点
  ```bash
  source ./devel/setup.zsh
  ```

  ```bash
  rosrun object_track object_track_node
  ```

- 运行 `my_detect` 节点
  ```bash
  source ./devel/setup.zsh
  ```

  ```bash
  rosrun object_detect my_detect.py
  ```

- 将遥控器offboard开关闭合，油门推至中位，无人机开始执行程序规划的路线：

  - 先起飞，起飞高度为 `TAKOFF_HIGH`
  - ......

- 程序退出方式：

  - 方法一（程序内写好的）：拨动6通道，使6通道的值大于1500
  - 方法二：`ctrl+c`

