#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <stdbool.h>
#include <cmath>

using namespace std;
using namespace cv;

const double PI = 3.14159265358979323846;

// added field member
typedef unsigned char byte;

// original field method
extern "C" __declspec(dllexport) double getRadian(double angle);
extern "C" __declspec(dllexport) double findMax(double arr[], int cnt);
extern "C" __declspec(dllexport) double findMin(double arr[], int cnt);
extern "C" __declspec(dllexport) Mat fillDstImg(Mat& dstImg, Mat& srcImg, double radian);
extern "C" __declspec(dllexport) bool isOutOfBounds(Mat& srcImg, double srcRow, double srcCol);
extern "C" __declspec(dllexport) void interpolateDstImg(Mat& dstImg, Mat& srcImg, int dstRow, int dstCol, double srcRow, double srcCol);
extern "C" __declspec(dllexport) void displayImg(Mat& image, const string displayName);

// added field method

extern "C" __declspec(dllexport) struct IMAGE
{
	int width;
	int height;
	int channels;
	uint8_t* data;
};

extern "C" __declspec(dllexport) IMAGE* readImg(char* imgPath);
extern "C" __declspec(dllexport) string type2str(int type);
extern "C" __declspec(dllexport) Mat bgr2bgra(Mat& imgBGR);
extern "C" __declspec(dllexport) IMAGE * createDstImg(IMAGE & srcImg, double angle);


