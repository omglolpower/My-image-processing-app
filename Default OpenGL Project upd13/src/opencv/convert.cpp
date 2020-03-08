#include "convert.h"
template<typename T>
float scf(T x_in)
{
	return static_cast<float>(x_in);
}
template<typename T>
unsigned char scuc(T x_in)
{
	return static_cast<unsigned char>(x_in);
}

cv::Mat convert_to_Y(cv::Mat& img)
{
	unsigned short Y = 0;
	cv::Mat resultImage = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
	for (unsigned int x = 0; x < img.cols; ++x)
	{
		for (unsigned int y = 0; y < img.rows; ++y)
		{

			Y = 36 * img.at<cv::Vec3b>(y, x)[2] +
				53 * img.at<cv::Vec3b>(y, x)[1] +
				11 * img.at<cv::Vec3b>(y, x)[0];
			Y /= 100;

			resultImage.at<uchar>(y, x) = static_cast<unsigned char>(Y);
		}
	}
	return resultImage;
}

cv::Mat two_tones(cv::Mat& img)
{
	cv::Mat resultImage = img.clone();
	for (unsigned int x = 0; x < img.cols; ++x)
	{
		for (unsigned int y = 0; y < img.rows; ++y)
		{

			if (resultImage.at<uchar>(y, x) < 128)
			{
				resultImage.at<uchar>(y, x) = 0;
			}
			else
			{
				resultImage.at<uchar>(y, x) = 255;
			}
			
		}
	}
	return resultImage;
}

cv::Mat fullRange(cv::Mat& c_in)
{
	cv::Mat r = c_in.clone();

	if (r.type() == 16)
	{
		for (char i = 0; i < 3; ++i)
		{
			unsigned char max = 0;
			for (unsigned int x = 0; x < r.cols; ++x)
			{
				for (unsigned int y = 0; y < r.rows; ++y)
				{
					if (r.at<cv::Vec3b>(y, x)[i] > max)
					{
						max = r.at<cv::Vec3b>(y, x)[i];
					}
				}
			}
			for (unsigned int x = 0; x < r.cols; ++x)
			{
				for (unsigned int y = 0; y < r.rows; ++y)
				{
					float f = scf((255 + max) / 255);
					r.at<cv::Vec3b>(y, x)[i] = scuc(scf(r.at<cv::Vec3b>(y, x)[i]) * f);
				}
			}
		}
	}
	else
	{
		unsigned char max = 0;
		for (unsigned int x = 0; x < r.cols; ++x)
		{
			for (unsigned int y = 0; y < r.rows; ++y)
			{
				if (r.at<uchar>(y, x) > max)
				{
					max = r.at<uchar>(y, x);
				}
			}
		}
		for (unsigned int x = 0; x < r.cols; ++x)
		{
			for (unsigned int y = 0; y < r.rows; ++y)
			{
				float f = scf((255 + max) / 255);
				r.at<uchar>(y, x) = scuc(scf(r.at<uchar>(y, x)) * f);
			}
		}
	}

	
	return r;
}