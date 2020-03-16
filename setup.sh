#!/bin/bash

echo 'install ROS KINETIC FUll VERSION'

#Step 1.2
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

#Step 1.3
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

#Step 1.4
sudo apt-get update
sudo apt-get install -y ros-kinetic-desktop-full

#Step 1.5
sudo rosdep init
rosdep update

#Step 1.6
echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
source ~/.bashrc

#Step 1.7
sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential


echo 'install GAZEBO for ROS KINETIC'
sudo apt-get install ros-kinetic-gazebo-ros-pkgs ros-kinetic-gazebo-ros-control