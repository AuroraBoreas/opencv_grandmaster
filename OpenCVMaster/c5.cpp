#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <iostream>

int main()
{
	std::string path("Resources/cards.jpg");
	cv::Mat img = cv::imread(path);
	cv::Mat imgWarp;

	// warp -> ordinary
	// src
	cv::Point2f src[4] = { {774, 107}, {1'019, 83}, {843,361}, {1'117,332} };
	// dst(mapped)
	float w{ 250 }, h{ 350 };
	cv::Point2f dst[4] = { {0.f,0.f}, {w, 0.f}, {0.f,h}, {w,h} }; 

	// transform
	cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
	cv::warpPerspective(img, imgWarp, matrix, cv::Point(w, h));

	// add mark
	for (int i = 0; i < 4; ++i)
	{
		cv::circle(img, src[i], 10, cv::Scalar(0, 0, 255), cv::FILLED);
	}

	cv::imshow("original", img);
	cv::imshow("warp", imgWarp);

	cv::waitKey(0);
	return 0;
}