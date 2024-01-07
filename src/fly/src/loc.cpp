#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "custom_gps_publisher");
    ros::NodeHandle nh;

    ros::Publisher gps_pub = nh.advertise<sensor_msgs::NavSatFix>("/mavros/global_position/global", 10);
    ros::Rate rate(1);  // Adjust the publishing rate as needed

    while (ros::ok())
    {
        sensor_msgs::NavSatFix gps_data;

        // Fill in your custom GPS data here
        gps_data.latitude = 37.7749;
        gps_data.longitude = -122.4194;
        gps_data.altitude = 10.0;

        gps_pub.publish(gps_data);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
