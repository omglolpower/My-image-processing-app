#include "pseudoColor.h"

cv::Mat pseudoColor(cv::Mat c_in)

{
	cv::Mat Y = convert_to_Y(c_in);
	cv::Mat r = cv::Mat::zeros(c_in.rows,c_in.cols, CV_8UC3);
	unsigned char pos[3] = { 0, 127, 255 };
	for (unsigned int x = 0; x < r.cols; ++x)
	{
		for (unsigned int y = 0; y < r.rows; ++y)
		{
			r.at<cv::Vec3b>(y, x)[2] = Y.at<uchar>(y, x);
			r.at<cv::Vec3b>(y, x)[1] = abs(Y.at<uchar>(y, x)-127)+127;
			r.at<cv::Vec3b>(y, x)[1] /= 3;
			r.at<cv::Vec3b>(y, x)[0] = 255 - Y.at<uchar>(y, x);
		}
	}
	return r;
}
