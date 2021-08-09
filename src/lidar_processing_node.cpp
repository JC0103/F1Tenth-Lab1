#include "chia_jing_cheng_lab1/lidar_processing.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "lidar_processing_node");

    Lab1 lab1;

    ros::spin();

    return(0);
}
