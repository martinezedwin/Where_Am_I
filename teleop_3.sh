#!/bin/bash

echo "sourcing"
source devel/setup.bash

echo "teleop to control bot"
rosrun teleop_twist_keyboard teleop_twist_keyboard.py
