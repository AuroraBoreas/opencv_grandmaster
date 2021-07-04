#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <iostream>

int main()
{
	std::string path{"Resources/test.JPG"};
	cv::Mat img = cv::imread(path);

	cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	// RGB -> Gray
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

	// Blur
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 5, 0);

	// Canny
	cv::Canny(imgBlur, imgCanny, 50, 150);

	// Dilate
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);

	// Erode
	cv::erode(imgDil, imgErode, kernel);

	cv::imshow("Image original", img);
	cv::imshow("Image cvtGray", imgGray);
	cv::imshow("Image Blur", imgBlur);
	cv::imshow("Image Canny", imgCanny);
	cv::imshow("Image Dilation", imgDil);
	cv::imshow("Image Erode", imgErode);

	cv::waitKey(0);

	return 0;
}