#include <iostream>
#include <thread>
#include "convert.h"
#include "Histogram.h"
#include "Levels.h"
#include <filesystem>
#define LOG(x) std::cout << x << std::endl;
template <typename T>
int sci(T &c)
{
	return static_cast<int>(c);
}
unsigned char iNumThreads = 36;
std::thread* threads = new std::thread[iNumThreads];



int opencv_main()
{
	{
		std::unique_ptr<cv::Mat> m1Y;
		{
			auto m1 = std::make_unique<cv::Mat>(cv::imread("res/images/img3.png"));

			cv::imshow("m1", *m1);
			{
				auto m1Y = std::make_unique<cv::Mat>(convert_to_Y(*m1));
				m1.reset();
				m1.release();
				
				{
					auto h1 = std::make_unique<cv::Mat>(getHist(*m1Y));
					cv::imshow("h1", *h1);
				}
				auto m2 = ChangeLevelsCount(*m1Y, 50, 0.0f);
				cv::imshow("m20", m2);
				auto m3 = ChangeLevelsCount(*m1Y, 50, 1.0f);
				cv::imshow("m21", m3);
				cv::imshow("m1Y", *m1Y);

			}
		}
	}

	

	cv::waitKey();
	return 0;
}