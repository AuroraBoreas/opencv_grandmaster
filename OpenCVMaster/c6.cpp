#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>

//int main()
//{
//	// color detection
//	std::string path("Resources/lambo.png");
//	cv::Mat img = cv::imread(path);
//	cv::Mat imgHSV, mask;
//
//	// RGB -> HSV
//	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
//
//	// find val of minmax_HSV
//	int hmin(0), smin(110), vmin(153);	// how do u find these values? using trackbar
//	int hmax(19), smax(240), vmax(255);	// how do u find these values? using trackbar
//
//	cv::Scalar lower(hmin, smin, vmin);
//	cv::Scalar upper(hmax, smax, vmax);
//
//	cv::inRange(imgHSV, lower, upper, mask);
//
//	cv::imshow("original", img);
//	cv::imshow("HSV", imgHSV);
//	cv::imshow("mask", mask);
//
//	cv::waitKey(0);
//	return 0;
//}

int main()
{
	//cv::String path("Resources/lambo.png"); 
	cv::String path("Resources/shapes.png");
	cv::Mat img = cv::imread(path);
	cv::Mat imgHSV, mask;
	
	// RGB -> HSV
	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	// window - trackbar: whenever using trackbar, using while loop;
	cv::namedWindow("Trackbars", (400, 200));
	int hmin(0), smin(0), vmin(0);
	int hmax(179), smax(255), vmax(255);
	cv::createTrackbar("Hue min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Sat min", "Trackbars", &smin, 255);
	cv::createTrackbar("Val min", "Trackbars", &vmin, 255);
	cv::createTrackbar("Hue max", "Trackbars", &hmax, 179);
	cv::createTrackbar("Sat max", "Trackbars", &smax, 255);
	cv::createTrackbar("Val max", "Trackbars", &vmax, 255);

	while (true)
	{
		// keep checking elements inbetween
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		cv::inRange(imgHSV, lower, upper, mask);

		cv::imshow("orignal", img);
		cv::imshow("HSV", imgHSV);
		cv::imshow("mask", mask);
		cv::waitKey(1);
	}
	

	
	return 0;
}