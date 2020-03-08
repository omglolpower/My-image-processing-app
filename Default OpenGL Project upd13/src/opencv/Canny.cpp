#include "Canny.h"

cv::Mat canny(cv::Mat& c_in)

{
	cv::Mat r = c_in.clone();
	cv::Canny(c_in, r, 100, 200);
	return r;
}