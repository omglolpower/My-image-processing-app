#include "Levels.h"


cv::Mat ChangeLevelsCount(cv::Mat& c, unsigned char L, float edge)
{
	cv::Mat* r = new cv::Mat;
	(*r) = cv::Mat::zeros(c.rows, c.cols, CV_8UC3);
	for (char i = 0; i < 3; ++i)
		for (unsigned int x = 0; x < (*r).cols; ++x)
			for (unsigned int y = 0; y < (*r).rows; ++y)
	{
		
		{
			for (unsigned char l = 0; l < 255 - L; l += L)
			{
				//c.at<cv::Vec3b>(y, x)[i] /= 2;
				if (c.at<cv::Vec3b>(y, x)[i] <= L)
				{
					(*r).at<cv::Vec3b>(y, x)[i] = static_cast<unsigned char>(static_cast<float>(L / 2) - static_cast<float>(L / 2) * edge);
					continue;
				}
				else if (c.at<cv::Vec3b>(y, x)[i] > 255 - L)
				{
					(*r).at<cv::Vec3b>(y, x)[i] = static_cast<unsigned char>(255.0f - (1.0f - edge) * (static_cast<float>(L / 2)));
					continue;


				}
				else if (c.at<cv::Vec3b>(y, x)[i] >= l && c.at<cv::Vec3b>(y, x)[i] < l + L)
					(*r).at<cv::Vec3b>(y, x)[i] = (l + L) / 2;
			}
		}
		
	}
	
	return (*r);
}
