﻿#include "RotateImg.h"

IMAGE* readImg(char* imgPath)
{
    Mat img = imread(imgPath);

    img = bgr2bgra(img);

    int imgSize = img.rows * img.cols * img.channels();

    uint8_t* imgPtr = new uint8_t[imgSize];

    memcpy(imgPtr, img.data, imgSize);

    IMAGE* image = new IMAGE();
    image->width = img.cols;
    image->height = img.rows;
    image->channels = img.channels();
    image->data = imgPtr;

    return image;
}

IMAGE* happyDay()
{
    IMAGE* image = new IMAGE();
    image->width = 100;
    image->height = 200;
    uint8_t* imgPtr = new uint8_t[100];
    image->data = imgPtr;

    return image;
}

Mat bgr2bgra(Mat& imgBGR)
{
    Mat imgBGRA;
    cvtColor(imgBGR, imgBGRA, COLOR_BGR2BGRA);
    return imgBGRA;
}

string type2str(int type) 
{
    string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch (depth) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
    }

    r += "C";
    r += (chans + '0');

    return r;
}

double getRadian(double angle)
{
    return angle * PI / 180;
}

void* createDstImg(int rows, int cols, double angle)
{
    double radian = getRadian(angle);

    double x1 = 0 - ((cols / 2) - 0.5);
    double y1 = 0 - ((rows / 2) - 0.5);

    double x2 = (cols - 1) - ((cols / 2) - 0.5);
    double y2 = 0 - ((rows / 2) - 0.5);

    double x3 = 0 - ((cols / 2) - 0.5);
    double y3 = (rows - 1) - ((rows / 2) - 0.5);

    double x4 = (cols - 1) - ((cols / 2) - 0.5);
    double y4 = (rows - 1) - ((rows / 2) - 0.5);

    double x1P = (x1 * cos(radian)) - (y1 * sin(radian));
    double y1P = (x1 * sin(radian)) + (y1 * cos(radian));

    double x2P = (x2 * cos(radian)) - (y2 * sin(radian));
    double y2P = (x2 * sin(radian)) + (y2 * cos(radian));

    double x3P = (x3 * cos(radian)) - (y3 * sin(radian));
    double y3P = (x3 * sin(radian)) + (y3 * cos(radian));

    double x4P = (x4 * cos(radian)) - (y4 * sin(radian));
    double y4P = (x4 * sin(radian)) + (y4 * cos(radian));

    double arrX[4] = { x1P, x2P, x3P, x4P };
    double arrY[4] = { y1P, y2P, y3P, y4P };

    double maxX = findMax(arrX, 4);
    double minX = findMin(arrX, 4);

    double maxY = findMax(arrY, 4);
    double minY = findMin(arrY, 4);

    double dstCol = maxX - minX;
    double dstRow = maxY - minY;

    Mat img(dstRow, dstCol, CV_8UC4, Scalar(255, 255, 255, 255)); // CV_8UC3 -> CV_8UC4

    int imgSize = img.rows * img.cols * img.channels();

    uint8_t* imgPtr = new uint8_t[imgSize];

    memcpy(imgPtr, img.data, imgSize);

    return imgPtr;
}

double findMax(double arr[], int cnt)
{
    double max = arr[0];

    for (int i = 0; i < cnt; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

double findMin(double arr[], int cnt)
{
    double min = arr[0];

    for (int i = 0; i < cnt; i++)
    {
        if (min > arr[i])
        {
            min = arr[i];
        }
    }
    return min;
}

Mat fillDstImg(Mat& dstImg, Mat& srcImg, double radian)
{
    for (int dstRow = 0; dstRow < dstImg.rows; dstRow++)
    {
        for (int dstCol = 0; dstCol < dstImg.cols; dstCol++)
        {
            double x = dstCol - ((dstImg.cols / 2) - 0.5);
            double y = dstRow - ((dstImg.rows / 2) - 0.5);

            double xP = (x * cos(radian)) + (y * sin(radian));
            double yP = ((-x) * sin(radian)) + (y * cos(radian));

            double srcRow = yP + ((srcImg.rows / 2) - 0.5);
            double srcCol = xP + ((srcImg.cols / 2) - 0.5);

            if (isOutOfBounds(srcImg, srcRow, srcCol))
            {
                continue;
            }

            interpolateDstImg(dstImg, srcImg, dstRow, dstCol, srcRow, srcCol);
        }
    }
    return dstImg;
}

bool isOutOfBounds(Mat& srcImg, double srcRow, double srcCol)
{
    if (srcRow < 0 || srcRow > srcImg.rows - 1)
    {
        return true;
    }
    if (srcCol < 0 || srcCol > srcImg.cols - 1)
    {
        return true;
    }
    return false;
}

void interpolateDstImg(Mat& dstImg, Mat& srcImg, int dstRow, int dstCol, double srcRow, double srcCol)
{
    for (int i = 0; i < 3; i++)
    {
        double weightHorizontal = srcCol - floor(srcCol);
        double weightVertical = srcRow - floor(srcRow);

        if (srcRow + 1 >= srcImg.rows && srcCol + 1 >= srcImg.cols) // right diagonal
        {
            dstImg.at<Vec3b>(dstRow, dstCol)[i] = srcImg.at<Vec3b>((int)srcRow, (int)srcCol)[i];
        }
        else if (srcCol + 1 >= srcImg.cols) // right
        {
            uchar pxRef = srcImg.at<Vec3b>((int)srcRow, (int)srcCol)[i];
            uchar pxToTheBottom = srcImg.at<Vec3b>((int)srcRow + 1, (int)srcCol)[i];

            uchar pxCentre = pxRef * (1 - weightVertical) + pxToTheBottom * weightVertical;

            dstImg.at<Vec3b>(dstRow, dstCol)[i] = pxCentre;
        }
        else if (srcRow + 1 >= srcImg.rows) // bottom
        {
            uchar pxRef = srcImg.at<Vec3b>((int)srcRow, (int)srcCol)[i];
            uchar pxToTheRight = srcImg.at<Vec3b>((int)srcRow, (int)srcCol + 1)[i];

            uchar pxCentre = pxRef * (1 - weightHorizontal) + pxToTheRight * weightHorizontal;

            dstImg.at<Vec3b>(dstRow, dstCol)[i] = pxCentre;
        }
        else
        {
            uchar pxRef = srcImg.at<Vec3b>((int)srcRow, (int)srcCol)[i];
            uchar pxToTheRight = srcImg.at<Vec3b>((int)srcRow, (int)srcCol + 1)[i];
            uchar pxToTheBottom = srcImg.at<Vec3b>((int)srcRow + 1, (int)srcCol)[i];
            uchar pxToTheRightDiagonal = srcImg.at<Vec3b>((int)srcRow + 1, (int)srcCol + 1)[i];

            uchar pxCentre = (pxRef * (1 - weightVertical) + pxToTheBottom * weightVertical) * (1 - weightHorizontal)
                + (pxToTheRight * (1 - weightVertical) + pxToTheRightDiagonal * weightVertical) * weightHorizontal;

            dstImg.at<Vec3b>(dstRow, dstCol)[i] = pxCentre;
        }
    }
}

void displayImg(Mat& image, string displayName)
{
    namedWindow(displayName, WINDOW_AUTOSIZE);
    imshow(displayName, image);
}