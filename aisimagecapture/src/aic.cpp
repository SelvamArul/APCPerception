#include <ros/ros.h>
#include <string>
#include <iostream>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>
#include <memory>
#include <boost/thread.hpp>

std::unique_ptr<image_transport::ImageTransport> g_it;
image_transport::Subscriber g_rgbSub;
image_transport::Subscriber g_depthSub;

void spinRGBthread()
{
	ros::spinOnce();
}

void spinDepththread()
{
	ros::spinOnce();
}

void depthTorgb(const cv::Mat& float_img, cv::Mat& rgb_img){
  if(rgb_img.rows != float_img.rows || rgb_img.cols != float_img.cols){
	  rgb_img = cv::Mat(float_img.size(), CV_8UC1);}
      cv::convertScaleAbs(float_img, rgb_img, 100, 0.0);
}
void rgbImageCallback(const sensor_msgs::ImageConstPtr& img)
{
	try
	{
		ROS_INFO_STREAM("Debug: In  RGB ImageCallback");
		cv::Mat image = cv_bridge::toCvShare(img, "rgb8")->image;
		cv::imwrite("testrgb.png",image);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("Could not convert from '%s' to 'rgb8'.", img->encoding.c_str());
	}
}
void depthImageCallback(const sensor_msgs::ImageConstPtr& img)
{
	cv_bridge::CvImagePtr cv_ptr;
	try
	{
		ROS_INFO_STREAM("Debug: In  Depth ImageCallback");
		cv_ptr = cv_bridge::toCvCopy(img);
		//cv::imwrite("testDepth.png",image);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR(" Failed Depth image subscription %s", e.what());
		return;
	}
	 cv::Mat depth_float_img = cv_ptr->image;
	 cv::Mat rgb_img;
	 depthTorgb(depth_float_img, rgb_img);
	 cv::imwrite("testdepth.png",rgb_img);
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "ImageCapture");
	ros::NodeHandle nh;
	boost::thread spinRGB_thread(&spinRGBthread);
	boost::thread spinDepth_thread(&spinDepththread);
	ROS_INFO_STREAM("Debug: Node up");
	g_it.reset(new image_transport::ImageTransport(nh));
	g_rgbSub = g_it->subscribe("/camera/rgb/image_rect_color", 1, &rgbImageCallback);
	g_depthSub = g_it->subscribe("/camera/depth/image_rect", 1, &depthImageCallback);
	bool canSpin = true;
	while (canSpin)
	{
		boost::thread spinRGB_thread(&spinRGBthread);
		boost::thread spinDepth_thread(&spinDepththread);
		canSpin = false;
	}

}
