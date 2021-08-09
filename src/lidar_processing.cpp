#include "chia_jing_cheng_lab1/lidar_processing.h"

Lab1::Lab1(): nh(){
    init_pub_sub();
}

//initialise subscriber and publishers
void Lab1::init_pub_sub(){
    scan_sub = nh.subscribe("/scan", 1000, &Lab1::ScanCB, this);
    closest_point_pub = nh.advertise<std_msgs::Float64>("/closest_point", 1000);
    farthest_point_pub = nh.advertise<std_msgs::Float64>("farthest_point", 1000);
    scan_range_pub = nh.advertise<chia_jing_cheng_lab1::scan_range>("/scan_range", 1000);
}

void Lab1::ScanCB(const sensor_msgs::LaserScan::ConstPtr& msg){
    ROS_INFO("Recevicing data from rostopic - /scan");
    ROS_INFO_ONCE("Sequence: %u", msg->header.seq);
    ROS_INFO_ONCE("TimeStamp: %f", msg ->header.stamp.toSec());
    ROS_INFO_ONCE("Frame ID: %s", msg->header.frame_id.c_str());
    ROS_INFO_ONCE("Start Angle of Scan(rad): %f", msg->angle_min);
    ROS_INFO_ONCE("End Angle of Scan(rad): %f", msg->angle_max);
    ROS_INFO_ONCE("Increment Angle(rad): %f", msg->angle_increment);
    ROS_INFO_ONCE("Time between measurement(s): %f", msg->time_increment);
    ROS_INFO_ONCE("Minimum Range(m): %f", msg->range_min);
    ROS_INFO_ONCE("Maximum Range(m): %f", msg->range_max);

    closest_point_msg.data = 999;
    farthest_point_msg.data = 0;
    for (int count = 0; count < msg->ranges.size(); count++){

        //Filter NANs and infs data
        if(!std::isinf(msg->ranges[count]) && !std::isnan(msg->ranges[count])){
            // ROS_INFO("Range %d : %f", count + 1, msg->ranges[count]);
            // ROS_INFO("Intensity %d : %f", count + 1, msg->intensities[count]);

            //Store into min or max range message if it is currently the smallest or largest respectively
            if(msg->ranges[count] < closest_point_msg.data){closest_point_msg.data = msg->ranges[count];}
            if(msg->ranges[count] > farthest_point_msg.data){farthest_point_msg.data = msg->ranges[count];}
        }
    }

    //Store the closest point and farthest point to the custom message
    scan_range_msg.min_dist = closest_point_msg.data;
    scan_range_msg.max_dist = farthest_point_msg.data;

    //Publish messages
    closest_point_pub.publish(closest_point_msg);
    farthest_point_pub.publish(farthest_point_msg);
    scan_range_pub.publish(scan_range_msg);
}

