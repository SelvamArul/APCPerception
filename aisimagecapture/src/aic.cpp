#include <ros/ros.h>
#include <string>
#include <iostream>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>
#include <memory>
#include <boost/thread.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <termios.h>
#include "boost/filesystem.hpp"

std::unique_ptr<image_transport::ImageTransport> g_it;
image_transport::Subscriber g_rgbSub;
image_transport::Subscriber g_depthSub;
bool g_canWrite = false;
boost::mutex g_lock;
std::string g_imgpath ="/home/arul/arul/APCImages/Image" ;
int g_imgCount = 0;
void depthTorgb(const cv::Mat& float_img, cv::Mat& rgb_img){
  if(rgb_img.rows != float_img.rows || rgb_img.cols != float_img.cols){
	  rgb_img = cv::Mat(float_img.size(), CV_8UC1);}
      cv::convertScaleAbs(float_img, rgb_img, 100, 0.0);
}

void syncCallback(const sensor_msgs::ImageConstPtr& rgb_img,const sensor_msgs::ImageConstPtr& depth_img)
{
	boost::mutex::scoped_lock lock(g_lock);
	if (g_canWrite)
	{
		cv_bridge::CvImagePtr cv_ptr;
		try
		{
			cv::Mat image = cv_bridge::toCvShare(rgb_img, "rgb8")->image;
			std::stringstream ss;
			ss << std::setw(3) << std::setfill('0') << g_imgCount++;

			std::string filename = g_imgpath + ss.str()+ "/rgb.png";
			boost::filesystem::path filePath ( g_imgpath + ss.str() );
			boost::system::error_code returnedError;
			boost::filesystem::create_directories( filePath, returnedError );
			if (!returnedError)
			{
				std::cout<<"Writing image to "<<filePath <<std::endl;
				cv::imwrite(filename,image);
				cv_ptr = cv_bridge::toCvCopy(depth_img);
				cv::Mat depth_float_img = cv_ptr->image;
				cv::Mat depth_img;
				depthTorgb(depth_float_img, depth_img);
				filename = g_imgpath + ss.str()+ "/depth.png";
				cv::imwrite(filename,depth_img);
				g_canWrite = false;
			}
		}
		catch (cv_bridge::Exception& e)
		{
			ROS_ERROR("Image save not successful  '%s' ", e.what());
		}
	}
}

int getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON);                 // disable buffering
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings
  int c = getchar();  // read character (non-blocking)
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}

void keyboardCallback()
{
	std::cout<<"Press Enterkey twice	 to save topic "<<std::endl;
	while (true)
	{
		 if( getchar() == 32 || getchar() == '\n')
		 {
			 g_canWrite = true;
		 }
	}
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "ImageCapture");
	ros::NodeHandle nh;
	message_filters::Subscriber<sensor_msgs::Image> rgb_sub(nh, "/camera/rgb/image_rect_color", 1);
    message_filters::Subscriber<sensor_msgs::Image> depth_sub(nh, "/camera/depth/image_rect", 1);
    message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image> sync(rgb_sub, depth_sub, 10);
    sync.registerCallback(boost::bind(&syncCallback, _1, _2));
    boost::thread keyboardThread(keyboardCallback);
    ros::spin();
    return 0;
}
