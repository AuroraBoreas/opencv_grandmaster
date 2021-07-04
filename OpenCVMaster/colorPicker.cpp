#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

inline void cTrackbar(int* hmin, int* smin, int* vmin, int* hmax, int* smax, int* vmax)
{
	cv::namedWindow("Trackbar", (640, 200));
	cv::createTrackbar("Hue min", "Trackbar", hmin, 179);
	cv::createTrackbar("Sat min", "Trackbar", smin, 255);
	cv::createTrackbar("Val min", "Trackbar", vmin, 255);
	cv::createTrackbar("Hue max", "Trackbar", hmax, 179);
	cv::createTrackbar("Sat max", "Trackbar", smax, 255);
	cv::createTrackbar("Val max", "Trackbar", vmax, 255);

	std::cout << *hmin << ", "
			  << *smin << ", " 
			  << *vmin << ", "
			  << *hmax << ", " 
			  << *smax << ", " 
			  << *vmax << std::endl;
}

int main()
{
	cv::VideoCapture cap(0);
	cv::Mat img, imgHSV, mask;

	int hmin(0), smin(0), vmin(0);
	int hmax(179), smax(255), vmax(255);

	cv::String path("Resources/test.JPG");
	img = cv::imread(path);
	cv::Scalar lower, upper;

	while (true)
	{
		// cap.read(img);
		lower = cv::Scalar(hmin, smin, vmin);
		upper = cv::Scalar(hmax, smax, vmax);

		cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
		cv::inRange(img, lower, upper, mask);
		cTrackbar(&hmin, &smin, &vmin, &hmax, &smax, &vmax);

		cv::imshow("Image", img);
		cv::imshow("Image HSV", imgHSV);
		cv::imshow("Image maks", mask);
		cv::waitKey(1);
	}

	return 0;
}