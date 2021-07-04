#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>

inline void getContour(cv::Mat imgDil, cv::Mat img)
{
	/// find contour
	std::vector<std::vector<cv::Point>> contour;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(imgDil, contour, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	
	/// draw contours on image
	//cv::drawContours(img, contour, -1, cv::Scalar(255, 0, 255), 2);

	/// find vertice(corner points)
	int area;
	float peri, aspRatio;
	int vertices;
	cv::String shapeType;

	std::vector<std::vector<cv::Point>> conPoly(contour.size());	// store vertice
	std::vector<cv::Rect> boundRect(contour.size());	// store rect, what for? : using method of Rect.tl(), Rect.br() cause we are lazy!

	for (int i = 0; i < contour.size(); ++i)
	{
		area = (int)cv::contourArea(contour[i]); /// detect contour area, using it to denoise
		std::cout << area << std::endl;

		if (area > 1'000)
		{ 
			peri = cv::arcLength(contour[i], true); /// detect length of contour
			cv::approxPolyDP(contour[i], conPoly[i], 0.02 * peri, true);
			cv::drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 2); // draw contour according to vertices

			std::cout << conPoly[i].size() << std::endl; // corner points

			boundRect[i] = cv::boundingRect(conPoly[i]);

			// draw rect
			cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
			vertices = (int)conPoly[i].size();

			aspRatio = (float)boundRect[i].width / boundRect[i].height;
			switch (vertices)
			{
			case 3: shapeType = "Triangle"; break;
			case 4: 
				if (aspRatio > 0.95 && aspRatio < 1.05) { shapeType = "Square"; }
				else { shapeType = "Rect"; }
				break;
			default:
				shapeType = "Circle";
				break;
			}

			cv::putText(img, shapeType,
				{ boundRect[i].x, boundRect[i].y - 5 },
				cv::FONT_HERSHEY_PLAIN,
				0.75,
				cv::Scalar(0, 0, 0), 
				1
			);
		}
	}
}

int main()
{
	cv::String path{"Resources/shapes.png"};
	cv::Mat img, imgGray, imgBlur, imgCanny, imgDil, imgErode;

	/// preprocessing: R CBCDE
	// r
	img = cv::imread(path);
	// c
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	// b
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 5, 0);
	// c
	cv::Canny(imgBlur, imgCanny, 50, 100);
	// d
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);
	// e
	cv::erode(imgDil, imgErode, kernel);


	// find contour
	getContour(imgDil, img);

	cv::imshow("Image original", img);
	//cv::imshow("Image gray", imgGray);
	//cv::imshow("Image blur", imgBlur);
	//cv::imshow("Image canny", imgCanny);
	//cv::imshow("Image dilate", imgDil);
	//cv::imshow("Image erode", imgErode);

	cv::waitKey(0);
	return 0;
}