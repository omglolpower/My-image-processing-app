#pragma once
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define UCFOR(x, e) for(unsigned char x = 0; x<e;++x)
#define UIFOR(x,n) for( unsigned int x = 0; x < n; ++x)
#define UIFORXY(x, y, c) for( unsigned int x = 0; x < c.cols; ++x)for (unsigned int y = 0; y < c.rows; ++y)
#define ZEROS(r,c) cv::Mat r = cv::Mat::zeros(c.rows, c.cols, CV_8UC1)
