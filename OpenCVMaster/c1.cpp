#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <iostream>


/// Images

//int main()
//{
//	std::string path("Resources/test.JPG");
//	cv::Mat img = cv::imread(path);
//	  
//	cv::imshow("Image", img);
//	cv::waitKey(0); // wait infinity
//
//	return 0; 
//}

/// Video
//int main()
//{
//	std::string path{"Resources/test_video.mp4"};
//	cv::VideoCapture vid(path);
//	cv::Mat img;
//
//	while (true)
//	{
//		vid.read(img);
//		cv::imshow("video", img);
//		cv::waitKey(1); // wait 1 second
//	}
//
//	return 0;
//}

/// Webcam, similar with video
//int main()
//{
//	cv::VideoCapture vid(0);	// webcam 0
//	cv::Mat img;
//
//	while (true)
//	{
//		vid.read(img);
//		cv::imshow("video", img);
//		cv::waitKey(1); // wait 1 second
//	}
//
//	return 0;
//}
