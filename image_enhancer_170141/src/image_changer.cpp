#include <ros/ros.h>
#include <image_transport/image_transport.h>

int brightness_change=0;
double contrast_factor=1.0;

image_transport::Publisher pub;

void imageCallback(const sensor_msgs::ImageConstPtr& pre_image)
{
        // created shared pointer Image
        sensor_msgs::Image::Ptr post_image = boost::make_shared<sensor_msgs::Image>();
        // copy image properties
        post_image->header = pre_image->header;
        post_image->height = pre_image->height;
        post_image->width = pre_image->width;
        post_image->encoding = pre_image->encoding;
        post_image->is_bigendian = pre_image->is_bigendian;
        post_image->step = pre_image->step;

        post_image->data.resize(post_image->step * post_image->height);//*pre_image->step);

        for(uint i=0; i<((post_image->height)*(post_image->step));i++)
        {
        post_image->data[i]=contrast_factor*(pre_image->data[i])+brightness_change;
        }
        pub.publish(post_image);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_changer");
    ros::NodeHandle nh;
    nh.setParam("/brighness", brightness_change);
    nh.setParam("/contrast", contrast_factor);
    nh.getParam("/brighness", brightness_change);
    nh.getParam("/contrast", contrast_factor);
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub;
    pub = it.advertise("cont_changer", 1);
    while(ros::ok())
    {
    sub = it.subscribe(argv[1], 1, imageCallback);
    nh.getParam("/brighness", brightness_change);
    nh.getParam("/contrast", contrast_factor);
    ros::spinOnce();
    }
        //printf("Im out! No error.");
}
