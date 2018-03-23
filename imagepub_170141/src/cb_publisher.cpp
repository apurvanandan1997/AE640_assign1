#include <ros/ros.h>
#include <image_transport/image_transport.h>

int main(int argc, char** argv)
{
  int frequency=5, width=640, height=640, square_size=64, pH=height, pW=width, pS=square_size;
  ros::init(argc, argv, "cb_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("cb_img", 1);

  nh.setParam("/height", height);
  nh.setParam("/width", width);
  nh.setParam("/square_size", square_size);
  nh.setParam("/frequency", frequency);
  nh.getParam("/height", height);
  nh.getParam("/width", width);
  nh.getParam("/square_size", square_size);
  nh.getParam("/frequency", frequency);
  pH=height, pW=width, pS=square_size;
  sensor_msgs::Image output_image;

  output_image.header.stamp     = ros::Time::now();
  output_image.height           = height;
  output_image.width            = width;
  output_image.encoding         = "rgb8";
  output_image.is_bigendian     = false;
  output_image.step             = 3 * width;

  ros::Rate loop_rate(frequency);

  for(int i=0;i<height;i++)//creating image
  {
    if((i/square_size)%2==0)
    {
        for(int j=0; j<(width/(2*square_size));j++)
        {
            for(int k=0; k<square_size; k++)
            {
                output_image.data.push_back(0);
                output_image.data.push_back(0);
                output_image.data.push_back(0);
            }
            for(int k=0; k<square_size; k++)
            {
                output_image.data.push_back(255);
                output_image.data.push_back(255);
                output_image.data.push_back(255);
            }
        }
    }
    else
    {
    for(int j=0; j<(width/(2*square_size));j++)
        {
            for(int k=0; k<square_size; k++)
            {
                output_image.data.push_back(255);
                output_image.data.push_back(255);
                output_image.data.push_back(255);
            }
            for(int k=0; k<square_size; k++)
            {
                output_image.data.push_back(0);
                output_image.data.push_back(0);
                output_image.data.push_back(0);
            }
        }
     }
  }
  while (nh.ok()) {//publishing it
      nh.getParam("/height", height);
      nh.getParam("/width", width);
      nh.getParam("/square_size", square_size);
      nh.getParam("/frequency", frequency);
     if(height!=pH||width!=pW||square_size!=pS)
    {
         pH=height, pW=width, pS=square_size;
         output_image.data.resize(0);
         output_image.header.stamp     = ros::Time::now();
         output_image.height           = height;
         output_image.width            = width;
         output_image.encoding         = "rgb8";
         output_image.is_bigendian     = false;
         output_image.step             = 3 * width;
      for(int i=0;i<height;i++)//creating image
      {
        if((i/square_size)%2==0)
        {
            for(int j=0; j<(width/(2*square_size));j++)
            {
                for(int k=0; k<square_size; k++)
                {
                    output_image.data.push_back(0);
                    output_image.data.push_back(0);
                    output_image.data.push_back(0);
                }
                for(int k=0; k<square_size; k++)
                {
                    output_image.data.push_back(255);
                    output_image.data.push_back(255);
                    output_image.data.push_back(255);
                }
            }
        }
        else
        {
        for(int j=0; j<(width/(2*square_size));j++)
            {
                for(int k=0; k<square_size; k++)
                {
                    output_image.data.push_back(255);
                    output_image.data.push_back(255);
                    output_image.data.push_back(255);
                }
                for(int k=0; k<square_size; k++)
                {
                    output_image.data.push_back(0);
                    output_image.data.push_back(0);
                    output_image.data.push_back(0);
                }
            }
         }
      }
     }
    ros::Rate loop_rate(frequency);
    pub.publish(output_image);
    ros::spinOnce();
    loop_rate.sleep();
  }
}


