#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>
#include <iostream>

std::vector<std::vector<int>> colors{ {}, {}, {} };

inline void findColor(cv::Mat img)
{
	int hmin(0), smin(0), vmin(0);
	int hmax(179), smax(255), vmax(255);

	cv::namedWindow("Trackbar", (640, 200));
	cv::createTrackbar("Hue min", "Trackbar", &hmin, 179);
	cv::createTrackbar("Sat min", "Trackbar", &smin, 255);
	cv::createTrackbar("Val min", "Trackbar", &vmin, 255);
	cv::createTrackbar("Hue max", "Trackbar", &hmax, 179);
	cv::createTrackbar("Sat max", "Trackbar", &smax, 255);
	cv::createTrackbar("Val max", "Trackbar", &vmax, 255);

	cv::Scalar lower, upper;
	cv::Mat imgHSV, mask;
	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	while (true)
	{
		lower = cv::Scalar(hmin, smin, vmin);
		upper = cv::Scalar(hmax, smax, vmax);
		cv::inRange(img, lower, upper, mask);

		cv::imshow("Image", img);
		cv::imshow("Image HSV", imgHSV);
	}
}

int main()
{
	cv::VideoCapture cap(0);
	cv::Mat img;

	while (true)
	{
		cap.read(img);
		cv::imshow("Image", img);
		cv::waitKey(1);
	}

	return 0;
}