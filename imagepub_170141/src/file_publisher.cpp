#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
  int frequency;
  std::string file;
  ros::init(argc, argv, "file_publisher");
  ros::NodeHandle nh;
  cv::Mat image;
  sensor_msgs::ImagePtr msg;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("image", 1);
  nh.setParam("/file", argv[1]);
  nh.setParam("/frequency", 5);
  while (nh.ok()) {
    nh.getParam("/frequency", frequency);
    ros::Rate loop_rate(frequency);
    nh.getParam("/file", file);
    image = cv::imread(file, CV_LOAD_IMAGE_COLOR);
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
}

