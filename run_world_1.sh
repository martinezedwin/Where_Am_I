#!/bin/bash

echo "Cleaning logs"
rosclean purge -y



echo "making....sourcing.....launching"
catkin_make && source devel/setup.bash && roslaunch my_robot world.launch 

#echo "sourcing"
#source devel/setup.bash

#echo "launching world"
#roslaunch my_robot world.launch 
