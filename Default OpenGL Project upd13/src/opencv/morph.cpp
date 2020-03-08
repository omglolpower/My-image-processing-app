#include "morph.h"
static int k = 1;
cv::Mat erosion(cv::Mat& c_in)
{
	cv::Mat r;
	if (c_in.type() == 16)
	{
		cv::Mat r1 = convert_to_Y(c_in);
		r = two_tones(r1);
	}
	else
	{
		r = two_tones(c_in);

	}
	cv::Mat r_compare = r.clone();

	for (int x = k; x < r.cols - k; ++x)
	{
		for (int y = k; y < r.rows - k; ++y)
		{
			for (int xx = x - k; xx <= x + k; ++xx)
			{
				for (int yy = y - k; yy <= y + k; ++yy)
				{
					if (r_compare.at<uchar>(yy, xx) == 0)
					{
						r.at<uchar>(y, x) = 0;
						break;
					}
				}
				if (r.at<uchar>(y, x) == 0)
				{
					break;
				}
			}
		}
	}
	return r;
}

cv::Mat dilation(cv::Mat& c_in)
{
	cv::Mat r;
	if (c_in.type() == 16)
	{
		cv::Mat r1 = convert_to_Y(c_in);
		r = two_tones(r1);
	}
	else
	{
		r = two_tones(c_in);

	}
	cv::Mat r_compare = r.clone();
	for (int x = k; x < r.cols - k; ++x)
	{
		for (int y = k; y < r.rows - k; ++y)
		{
			for (int xx = x - k; xx <= x + k; ++xx)
			{
				for (int yy = y - k; yy <= y + k; ++yy)
				{
					if (r_compare.at<uchar>(yy, xx) == 255)
					{
						r.at<uchar>(y, x) = 255;
						break;
					}
				}
				if (r.at<uchar>(y, x) == 255)
				{
					break;
				}
			}
		}
	}
	return r;
}

cv::Mat opening(cv::Mat& c_in)
{
	cv::Mat r = erosion(c_in);
	return dilation(r);
}
cv::Mat cvsum(cv::Mat& c_in1, cv::Mat& c_in2)
{
	cv::Mat r = c_in1.clone();
	for (unsigned int x = 0; x < r.cols; ++x)
	{
		for (unsigned int y = 0; y < r.rows; ++y)
		{
			r.at<uchar>(y, x) += c_in2.at<uchar>(y, x);
		}
	}
	return r;
}
cv::Mat cvsbs(cv::Mat& c_in1, cv::Mat& c_in2)
{
	cv::Mat r = c_in1.clone();
	for (unsigned int x = 0; x < r.cols; ++x)
	{
		for (unsigned int y = 0; y < r.rows; ++y)
		{
			r.at<uchar>(y, x) -= c_in2.at<uchar>(y, x);
		}
	}
	return r;
}
cv::Mat closing(cv::Mat& c_in)
{

	cv::Mat r = dilation(c_in);
	return erosion(r);
}

cv::Mat MG(cv::Mat& c_in)
{
	cv::Mat r0 = convert_to_Y(c_in);
	cv::Mat r = cv::Mat::zeros(c_in.size(), CV_8U);
	for (char i = 0; i < 3; ++i)
	{
		cv::Mat r1 = dilation(r0);
		cv::Mat r2 = erosion(r0);
		cv::Mat r3 = cvsbs(r1, r2);
		--k;
		cv::Mat r4 = erosion(r3);
		for (unsigned int x = 0; x < r.cols; ++x)
		{
			for (unsigned int y = 0; y < r.rows; ++y)
			{
				r4.at<uchar>(y, x) /= 3;
			}
		}
		cv::Mat r5 = cvsum(r, r4);
		r = r5.clone();
		++k; ++k;
	}

	k = 1;
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
			if (r.at<uchar>(y, x) > max)
			{
				r.at<uchar>(y, x) += 255 - max;
			}
		}
	}
	return r;
}
