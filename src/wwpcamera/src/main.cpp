#include <ros/ros.h>
#include "/home/guilherme/wwpcamera/src/wwpcamera/src/backend.h"
#include <string>
int main(int argc, char** argv) {
    ros::init(argc, argv, "meu_node");
    ros::NodeHandle nh;

    Backend backend;

    ROS_INFO("O nó ROS esta funcionando!");
    ROS_INFO("%s", backend.getAuthMessage().c_str());
    ros::spin();
    return 0;
}
