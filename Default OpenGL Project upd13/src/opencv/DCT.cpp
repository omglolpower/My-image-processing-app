#include "DCT.h"
#include "convert.h"
#include <math.h>
#define PI()	3.14f
int f(int i)
{
	if (i == 0) return 1 / static_cast<int>(sqrt(2));
	else return 1;
}

cv::Mat DCT(cv::Mat& c_in)
{
	int M = c_in.rows;
	float Mf = static_cast<float>(M);
	cv::Mat r = cv::Mat::zeros(M, M, CV_8UC1);
	cv::Mat c = convert_to_Y(c_in);
	unsigned char p = 0;
	float xf, yf, uf, vf;
	// Create 2D array of pointers:
	float** rf = new float*[M];
	for (int i = 0; i < M; ++i) {
		rf[i] = new float[M];
	}

	// Null out the pointers contained in the array:
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			rf[i][j] = 0.0f;
		}
	}
	for (int u = 0; u < M; ++u)
	{
		uf = static_cast<float>(u);

		for (int v = 0; v < M; ++v)
		{
			vf = static_cast<float>(v);

			for (int x = 0; x < M; ++x)
			{
				xf = static_cast<float>(x);
				for (int y = 0; y < M; ++y)
				{
					yf = static_cast<float>(y);

					rf[u][v] += 
						(2.0f / Mf) * static_cast<float>(f(x) * f(y))
						* cosf(PI() * uf / (2.0f * Mf) * (2.0f * xf+1.0f))
						* cosf(PI() * vf / (2.0f * Mf) * (2.0f * yf+1.0f))
						* static_cast<float>(c.at<uchar>(x, y))
						;
						
				}
			}
		}
	}

	for (int u = 0; u < M; ++u)
	{
		for (int v = 0; v < M; ++v)
		{
			r.at<uchar>(u, v) = static_cast<unsigned char>(rf[u][v]);
		}
	}
	cv::Mat* r1 = new cv::Mat;
	(*r1) = r.clone();
	cv::resize(r, *r1, cv::Size(), 8, 8, cv::INTER_LINEAR);
	return *r1;
}
