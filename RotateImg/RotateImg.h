#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdbool.h>
#include <cmath>

using namespace std;
using namespace cv;

const double PI = 3.14159265358979323846;

extern "C" __declspec(dllexport) Mat readImage(char* imgPath);
extern "C" __declspec(dllexport) double getRadian(double angle);
extern "C" __declspec(dllexport) Mat createDstImg(Mat& srcImg, double angle);
extern "C" __declspec(dllexport) double findMax(double arr[], int cnt);
extern "C" __declspec(dllexport) double findMin(double arr[], int cnt);
extern "C" __declspec(dllexport) Mat fillDstImg(Mat& dstImg, Mat& srcImg, double radian);
extern "C" __declspec(dllexport) bool isOutOfBounds(Mat& srcImg, double srcRow, double srcCol);
extern "C" __declspec(dllexport) void interpolateDstImg(Mat& dstImg, Mat& srcImg, int dstRow, int dstCol, double srcRow, double srcCol);
extern "C" __declspec(dllexport) void displayImage(Mat& image, const string displayName);