
#include "Histogram.h"

cv::Mat getHist(cv::Mat& img)
{
	cv::Mat hist = cv::Mat::zeros(1, 256, CV_64FC1);
	for (int x = 0; x < img.cols; x++)
		for (int y = 0; y < img.rows; y++) {
			int r = img.at<unsigned char>(y, x);
			hist.at<double>(0, r) = hist.at<double>(0, r) + 1.0;
		}
	double m = 0, M = 0;
	cv::minMaxLoc(hist, &m, &M);
	hist = hist / M;
	cv::Mat hist_img = cv::Mat::zeros(100, 256, CV_8U);
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 100; y++) {
			if (hist.at<double>(0, x) * 100 > y) {
				hist_img.at<unsigned char>(99 - y, x) = 255;
			}
		}
	cv::bitwise_not(hist_img, hist_img);
	return hist_img;
}