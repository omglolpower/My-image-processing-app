#pragma once
#include "opencv.h"
#include <math.h>
template<typename T>
float scf(T x_in);
template<typename T>
unsigned char scuc(T x_in);
cv::Mat convert_to_Y(cv::Mat& img);
cv::Mat two_tones(cv::Mat& img);
cv::Mat fullRange(cv::Mat& c_in);