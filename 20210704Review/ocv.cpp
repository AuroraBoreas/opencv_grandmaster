#include "ocv.h"

void TS::readImage(void)
{
	/// Image
	cv::String path{ "Resources/test.JPG" };
	cv::Mat img;

	img = cv::imread(path);

	cv::imshow("Image", img);
	cv::waitKey(0);
}

void TS::readVideo(void)
{
	/// Video
	cv::String path("Resources/test_video.mp4");
	cv::VideoCapture cap(path);
	cv::Mat img;

	try
	{
		while (true)
		{
			cap.read(img);

			cv::imshow("Video", img);
			cv::waitKey(10);
		}
	}
	catch (const cv::Exception& e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}

}

void TS::readWebcam(void)
{
	/// Webcam
	cv::VideoCapture cap(0);
	cv::Mat img;

	while (true)
	{
		cap.read(img);

		cv::imshow("Webcam", img);
		cv::waitKey(1);
	}
}

void TS::prepImage(void)
{
	/// R C B C D E
	cv::String path("Resources/test.JPG");
	cv::Mat img, imgGray, imgBlur, imgCanny, imgDil, imgErode;

	img = cv::imread(path);
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 5, 0);
	cv::Canny(imgBlur, imgCanny, 50, 100);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);
	cv::erode(imgDil, imgErode, kernel);

	cv::imshow("Image original", img);
	cv::imshow("Image Gray", imgGray);
	cv::imshow("Image Blur", imgBlur);
	cv::imshow("Image Canny", imgCanny);
	cv::imshow("Image Dilate", imgDil);
	cv::imshow("Image Erode", imgErode);

	cv::waitKey(0);
}

void TS::resizeImage(void)
{
	cv::String path{"Resources/test.JPG"};
	cv::Mat img, imgResize, imgCrop;

	img = cv::imread(path);
	// cv::resize(img, imgResize, cv::Size(100, 100)); // by asp w/h
	cv::resize(img, imgResize, cv::Size(), 0.5, 0.5); // by asp ratio

	cv::Rect rect(100, 100, 200, 200);
	imgCrop = img(rect);

	cv::imshow("Image original", img);
	cv::imshow("Image Resize", imgResize);
	cv::imshow("Image Crop", imgCrop);

	cv::waitKey(0);
}

void TS::drawImage(void)
{
	cv::Mat img;
	img = cv::Mat(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));
	
	// line
	cv::line(img, cv::Point(100, 200), cv::Point(100, 400), cv::Scalar(0, 255, 255), 2);
	// circle
	cv::circle(img, cv::Point(256, 256), 100, cv::Scalar(0, 255, 0), 2);
	// rectangle
	cv::rectangle(img, cv::Rect(300, 200, 50, 50), cv::Scalar(255, 0, 0), 2);
	// putText
	cv::putText(img, "CSN SCY", cv::Point(106, 100), 
		cv::FONT_HERSHEY_PLAIN, 5,
		cv::Scalar(255, 0, 255), 2);

	cv::imshow("Image", img);
	cv::waitKey(0);
}

void TS::warpImage(void)
{
	cv::String path("Resources/cards.jpg");
	cv::Mat img, imgWarp, matrix;

	img = cv::imread(path);
	
	cv::Point2f src[4] = { {62,322}, {340,277},{88, 636},{403, 574} };
	float w(250), h(350);
	cv::Point2f dst[4] = { {0.f, 0.f},{w, 0.f},{0.f, h},{w, h} };

	matrix = cv::getPerspectiveTransform(src, dst);
	cv::warpPerspective(img, imgWarp, matrix, cv::Point(w, h));

	cv::imshow("Image", img);
	cv::imshow("Image warp", imgWarp);

	cv::waitKey(0);
}

void TS::maskImage(void)
{
	cv::String path("Resources/shapes.png");
	cv::Mat img, imgHSV, mask;

	img = cv::imread(path);
	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	int hmin(0), smin(0), vmin(0);
	int hmax(179), smax(255), vmax(255);
	cv::Scalar lower, upper;

	/// trackbar
	cv::namedWindow("Trackbar", (640, 200));
	cv::createTrackbar("Hue min", "Trackbar", &hmin, 179);
	cv::createTrackbar("Sat min", "Trackbar", &smin, 255);
	cv::createTrackbar("Val min", "Trackbar", &vmin, 255);
	cv::createTrackbar("Hue max", "Trackbar", &hmax, 179);
	cv::createTrackbar("Sat max", "Trackbar", &smax, 255);
	cv::createTrackbar("Val max", "Trackbar", &vmax, 255);

	while (true)
	{
		lower = cv::Scalar(hmin, smin, vmin);
		upper = cv::Scalar(hmax, smax, vmax);

		cv::inRange(img, lower, upper, mask);

		cv::imshow("Image", img);
		cv::imshow("Image HSV", imgHSV);
		cv::imshow("Image mask", mask);
		cv::waitKey(1);
	}
}
void TS::getContour(cv::Mat imgErode, cv::Mat img)
{
	///find contour
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(imgErode, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	///draw contour
	//cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);

	int area;
	double peri;
	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect;
	cv::String shapeType;
	///detect area, periphery, polygon, vertices
	for (int i = 0; i < contours.size(); ++i)
	{
		area = (int)cv::contourArea(contours[i]); // area
		std::cout << area << std::endl;
		peri = cv::arcLength(contours[i], true); // periphery
		cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true); // polygon
		std::cout << conPoly[i].size() << std::endl; // vertice
		boundRect.emplace_back(cv::boundingRect(conPoly[i]));

		int vertices = (int)conPoly[i].size();
		double aspRatio = (double)boundRect[i].width / boundRect[i].height;
		switch (vertices)
		{
		case 3: shapeType = "Tri"; break;
		case 4:
			if (aspRatio > 0.95 && aspRatio < 1.05) { shapeType = "Square"; }
			else { shapeType = "Rect"; }
			break;
		default:
			shapeType = "Circle";
			break;
		}
		cv::rectangle(img, boundRect[i], cv::Scalar(0, 255, 0), 2);
		cv::putText(img, shapeType, cv::Point(boundRect[i].x, boundRect[i].y - 5), cv::FONT_HERSHEY_PLAIN, .75, cv::Scalar(0, 42, 69), 1);
	}
}

void TS::detectContour(void)
{
	cv::String path("Resources/shapes.png");
	cv::Mat img, imgGray, imgBlur, imgCanny, imgDil, imgErode, kernel;
	img = cv::imread(path);
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 5, 0);
	cv::Canny(imgBlur, imgCanny, 50, 100);
	kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);
	//cv::erode(imgDil, imgErode, kernel);

	TS::getContour(imgDil, img);
	
	cv::imshow("Image", img);

	cv::waitKey(0);
}