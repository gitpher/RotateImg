#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];
    double angle = atof(argv[2]);

    
    Mat srcImg = imread(imgPath);
    Mat dstImg(srcImg.rows, srcImg.cols, CV_8UC3, Scalar(0, 0, 0));

    double PI = 3.1415926;
    double radian = angle * PI / 180;

    // print original
    // moving center



    for (int row = 0; row < dstImg.rows ; row++)
    {
        for (int col = 0; col < dstImg.cols; col++)
        {
            int x = col;
            int y = row;

            int xPrime = (x * cos(radian)) + (y * sin(radian));
            int yPrime = (x * sin(radian)) - (y * cos(radian));

            int newX = xPrime + (dstImg.cols / 2); // 
            int newY = yPrime - (dstImg.rows / 2); // 

            if (newX < 0 || newX >= dstImg.cols)
            {
                continue;
            }
            if (newY < 0 || newY >= dstImg.rows)
            {
                continue;
            }

            dstImg.at<Vec3b>(newX, newY) = srcImg.at<Vec3b>(x, y);
        }
    }
    

    namedWindow("ORIGINAL IMAGE", WINDOW_AUTOSIZE);
    imshow("ORIGINAL IMAGE", srcImg);
    // print modified
    namedWindow("MODIFIED IMAGE", WINDOW_AUTOSIZE);
    imshow("MODIFIED IMAGE", dstImg);
    waitKey(0);

    return 0;
}

// add const