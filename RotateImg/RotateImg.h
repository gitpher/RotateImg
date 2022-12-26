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

double getRadian(double angle);
Mat createDstImg(Mat& srcImg, double angle);
void fillDstImg(Mat& dstImg, Mat& srcImg, double radian);
bool isOutOfBounds(Mat& dstImg, Mat& srcImg, int dstRow, int dstCol, float srcRow, float srcCol);
void interpolateDstImg(Mat& dstImg, Mat& srcImg, int dstRow, int dstCol, double srcRow, double srcCol);
void displayImage(Mat& image, const string displayName);
