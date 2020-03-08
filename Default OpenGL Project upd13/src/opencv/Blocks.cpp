#include "Blocks.h"

cv::Mat blocks(cv::Mat& c_in)
{
	cv::Mat imageWithBlocks = c_in.clone();
	int blockSize = 32;
	for (int y = 0; y < c_in.rows; y = y + blockSize) {
		for (int x = 0; x < c_in.cols; x = x + blockSize) {
			cv::Rect block = cv::Rect(x, y, blockSize, blockSize);			rectangle(imageWithBlocks, block, cv::Scalar(0, 255, 0));
		}
	}
	return imageWithBlocks;
}
