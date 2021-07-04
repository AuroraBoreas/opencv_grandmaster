#pragma once
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

namespace TS
{
	void readImage(void);
	void readVideo(void);
	void readWebcam(void);

	void prepImage(void);
	void resizeImage(void);
	void drawImage(void);
	void warpImage(void);
	void maskImage(void);
	void detectContour(void);

	void getContour(cv::Mat, cv::Mat);

}