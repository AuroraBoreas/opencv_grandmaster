#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>

int main()
{
	std::string path{"Resources/test.JPG"};
	cv::Mat img = cv::imread(path);
	cv::Mat imgResize, imgCrop;

	// resize
	std::cout << img.size << std::endl;
	// by user-defined width and height
	cv::resize(img, imgResize, cv::Size(100,100));
	// by aspect ratio
	cv::resize(img, imgResize, cv::Size(), 0.5, 0.5);

	// crop
	cv::Rect rect(100, 100, 300, 250);
	imgCrop = img(rect);


	cv::imshow("Original", img);
	cv::imshow("Resized", imgResize);
	cv::imshow("Cropped", imgCrop);

	cv::waitKey(0);

	return 0;
}