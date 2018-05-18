#!/bin/bash
source ./devel/setup.bash
hostname –I 1.1.1.2
export ROS_IP=1.1.1.2
rosrun con_esc esc_input
