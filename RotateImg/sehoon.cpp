#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace cv;
using namespace std;
int get_side_length(int x, int y);
void rotate_and_paste(Mat* origin, Mat* rotated, int degree);
int main(int argc, char* argv[])
{
	// 1. initialize
	// 1-1. 명령인자를 받는다.
	string image_name = argv[1];
	int degree = atoi(argv[2]);
	// 1-2. '원본 이미지'와 그것을 '복사해 회전시킬 이미지'를 준비한다.
	Mat origin_image = imread(image_name);
	int origin_image_rows = origin_image.rows;
	int origin_image_cols = origin_image.cols;
	std::cout << "rows :" << origin_image_rows << std::endl;
	std::cout << "cols :" << origin_image_cols << std::endl;
	Mat rotated_image = Mat(
		get_side_length(origin_image_rows, origin_image_cols),
		get_side_length(origin_image_rows, origin_image_cols),
		CV_8UC3
	);
	rotated_image.setTo(Scalar(255, 13, 65));
	// 2. rotate and copy
	rotate_and_paste(&origin_image, &rotated_image, degree);
	// 3. print two images(origin image and rotated image)
	imshow("origin", origin_image);
	imshow("rotated", rotated_image);
	waitKey(0);
	return 0;
}
int get_side_length(int x, int y) // F1. 이름 어떻게 할까?
{
	return sqrt(pow(x, 2) + pow(y, 2)) * 2; // F2. 일단 곱하기 2로 크기를 늘렸는데 이는 차차 최적화합시다.
}
void rotate_and_paste(Mat* origin, Mat* rotated, int degree)
{
	for (int i = 0; i < origin->rows; i++)
	{
		for (int j = 0; j < origin->cols * 3; j++)
		{
			// 1. push up
			int x = origin->rows - i;
			int y = j;

			// 2. rotate			
			int _x = cos(degree) * x - sin(degree) * y;
			int _y = sin(degree) * x + cos(degree) * y;
			//std::cout << "X :" << _x << "\n" << std::endl;
			//std::cout << "Y :" << _y << "\n" << std::endl;
			// 3. push down
			rotated->at<uchar>(_x, _y) = origin->at<uchar>(i, j);
		}
	}
}