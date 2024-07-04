#include <ros/ros.h>
#include "backend.h"

#include <string>

int main(int argc, char** argv) {
    ros::init(argc, argv, "meu_node");
    ros::NodeHandle nh;

    Backend backend;

    ROS_INFO("O nó ROS está funcionando!");
    backend.loadImage();
    // Tentar ativar o SDK
   
    ros::spin();
    return 0;
}
