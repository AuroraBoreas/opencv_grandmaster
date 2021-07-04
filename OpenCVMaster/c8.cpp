#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main()
{
	cv::String path{ "Resources/test.JPG" };
	cv::String ccXml("Resources/haarcascade_frontalface_default.xml");
	cv::Mat img;

	img = cv::imread(path);

	// load cascade classifier
	cv::CascadeClassifier facecascade;
	facecascade.load(ccXml);
	if (facecascade.empty()) { std::cout << "XML file not found!" << std::endl; }

	// detect
	std::vector<cv::Rect> faces;
	facecascade.detectMultiScale(img, faces);
	/// failed to detect face hah;
	std::for_each(faces.begin(), faces.end(), [&](const cv::Rect& e) {
		cv::rectangle(img, e.tl(), e.br(), cv::Scalar(255, 0, 255));
		});

	cv::imshow("Image original", img);
	cv::waitKey(0);
	return 0;
}