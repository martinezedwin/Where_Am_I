#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    //ROS_INFO_STREAM("Moving the robot");

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    //ROS_INFO_STREAM("moving the robot");
    //if (!client.call(srv)){
    //    ROS_INFO_STREAM("Failed to execute drive command");
    //}
    client.call(srv);
}

// This callback function continuously executes and reads the image data


void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;


    //-----------------------------------------------------------------Image Info-------------------------------------------------------
    int image_step = img.step;
    int image_width = img.width;
    int image_height = img.height;
    std::string encoding = img.encoding;
    int image_size = img.data.size();

    //ROS_INFO_STREAM("Step = " << image_step);    //output is 2400
    //ROS_INFO_STREAM("Width = " << image_width);  //800
    //ROS_INFO_STREAM("Height = " << image_height);//800
    //ROS_INFO_STREAM("Encoding = " << encoding);  //rgb8
    //ROS_INFO_STREAM("size = " << image_size);  //1920000
    //-----------------------------------------------------------------^Image Info^-------------------------------------------------------

    //Define the thirds
    int first_third_bound = (image_step / 3);
    int second_third_bound = (image_step * 2 / 3);
    int end_of_image = image_step;

    //ROS_INFO_STREAM("First Bound = " << first_third_bound);    //800
    //ROS_INFO_STREAM("Second Bound = " << second_third_bound);  //1600
    //ROS_INFO_STREAM("Third Bound = " << end_of_image);         //2400

    float x = 0.0;
    float z = 0.5; //rotate around the z axis until you find the ball

    int where_am_i = 1;
    bool found_ball = false;

    for (int i = 0; i < image_size; i+=3) {                                      //loop through every pixel in an image

        if (where_am_i > image_step){
            where_am_i = 1;
        }
        if (img.data[i] == white_pixel && img.data[i+1]==white_pixel && img.data[i+2]==white_pixel) {
            //ROS_INFO_STREAM(img.data[i]);
            if (where_am_i <= first_third_bound){
                //ROS_INFO_STREAM("position = " <<where_am_i );
                ROS_INFO_STREAM("IT'S LEFT!!!!!!!!!!!!!!!!!!!");
                x = 0.1;
                z = 0.1;
            }
            else if (where_am_i > first_third_bound && where_am_i <= second_third_bound){
                //ROS_INFO_STREAM("position = " <<where_am_i );
                ROS_INFO_STREAM("IT'S MIDDLE!!!!!!!!!!!!!!!!!!!");
                x = 0.1;
                z = 0.0;
            }
            else if (where_am_i > second_third_bound){
                //ROS_INFO_STREAM("position = " <<where_am_i );
                ROS_INFO_STREAM("IT'S RIGHT!!!!!!!!!!!!!!!!!!!");
                x = 0.1;
                z = -0.1;
            }
            
        }
        //ROS_INFO_STREAM("i = " << i);
        //ROS_INFO_STREAM("out of loop position = " <<where_am_i );
        where_am_i += 3;
    }

    //ROS_INFO_STREAM("x = " << x <<", "<< "z = "<< z);
    drive_robot(x, z);

}


int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
