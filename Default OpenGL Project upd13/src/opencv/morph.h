#pragma once
#include "convert.h"
cv::Mat erosion(cv::Mat& c_in);

cv::Mat dilation(cv::Mat& c_in);

cv::Mat opening(cv::Mat& c_in);
cv::Mat cvsum(cv::Mat& c_in1, cv::Mat& c_in2);
cv::Mat cvsbs(cv::Mat& c_in1, cv::Mat& c_in2);
cv::Mat closing(cv::Mat& c_in);
cv::Mat MG(cv::Mat& c_in);