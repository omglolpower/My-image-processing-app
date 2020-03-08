#include "Gauss.h"


cv::Mat gauss3( cv::Mat& c_in)
{
cv::Mat input_img = convert_to_Y(c_in);
	cv::Mat output_img = cv::Mat::zeros(input_img.size(), CV_8U);
	float k = 36; // коэффициент нормировки
	float Fk[3][3] = { {1,4,1},	{4,16,4},	{1,4,1} }; // маска фильтра
	for (int i = 1; i < input_img.cols - 1; i++)
		for (int j = 1; j < input_img.rows - 1; j++) {
			// далее производим свертку
			float conv = 0;
			for (int ii = -1; ii <= 1; ii++)
				for (int jj = -1; jj <= 1; jj++) {
					uchar blurred = input_img.at<uchar>(j + jj, i + ii);
					conv += Fk[ii + 1][jj + 1] * blurred;
				}
			uchar blurred = conv / k; // осуществляем нормировку
			output_img.at<uchar>(j, i) = blurred;
		}
	return output_img;
}

cv::Mat gauss5(cv::Mat& c_in)
{
	cv::Mat input_img = convert_to_Y(c_in);
	cv::Mat output_img = cv::Mat::zeros(input_img.size(), CV_8U);
	float k = 256; // коэффициент нормировки
	k *= 3;
	float Fk[5][5] = { {1,4,16,4, 1},{4,16,64,16,4},	{16,64,256,65,16},{4,16,64,16,4},{1,4,16,4, 1} }; // маска фильтра
	for (int i = 2; i < input_img.cols - 2; i++)
		for (int j = 2; j < input_img.rows - 2; j++) {
			// далее производим свертку
			float conv = 0;
			for (int ii = -2; ii <= 2; ii++)
				for (int jj = -2; jj <= 2; jj++) {
					uchar blurred = input_img.at<uchar>(j + jj, i + ii);
					conv += Fk[ii + 2][jj + 2] * blurred / k;
				}
			uchar blurred = conv; // осуществляем нормировку
			output_img.at<uchar>(j, i) = blurred;
		}
	return output_img;
}