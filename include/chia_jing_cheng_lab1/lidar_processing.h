#ifndef LAB1_H
#define LAB1_H

#include <ros/ros.h>

#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float64.h>
#include "chia_jing_cheng_lab1/scan_range.h"

class Lab1{
public:
    Lab1();
    
    void init_pub_sub();

private:
    ros::NodeHandle nh;

    //Declare subscriber
    ros::Subscriber scan_sub;

    //Declare publishers
    ros::Publisher closest_point_pub;
    ros::Publisher farthest_point_pub;
    ros::Publisher scan_range_pub;

    //Callback function
    void ScanCB(const sensor_msgs::LaserScan::ConstPtr& msg);

    //variables
    std_msgs::Float64 closest_point_msg;
    std_msgs::Float64 farthest_point_msg;
    chia_jing_cheng_lab1::scan_range scan_range_msg;
};

#endif