#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>

int main()
{
	// draw image: by default, rect
	cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255)); // white

	// circle on img
	cv::circle(img, cv::Point(256, 256), 155, cv::Scalar(0, 0, 255), 5);
	// rectangle on img
	cv::rectangle(img, cv::Rect(100, 100, 100, 100), cv::Scalar(255, 0, 0), cv::FILLED);
	// line
	cv::line(img, cv::Point(130, 130), cv::Point(382, 250), cv::Scalar(0, 255, 0), 3);
	// text
	cv::putText(img, "hello SCY", cv::Point(50, 50), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0, 0, 0), 1);


	cv::imshow("draw", img);

	cv::waitKey(0);
	return 0;
}