#!/bin/bash

echo "sourcing"
source devel/setup.bash

echo "launching cam visalization"
rosrun rqt_image_view rqt_image_view

#step = 2400
#height = 800