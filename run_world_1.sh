#!/bin/bash

echo "Cleaning logs"
rosclean purge -y

echo "making...."
catkin_make

echo "sourcing"
source devel/setup.bash

echo "launching world"
roslaunch my_robot world.launch 
