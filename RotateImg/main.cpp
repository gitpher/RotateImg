#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];
    double angle = atof(argv[2]);

    double PI = 3.1415926;
    double radian = angle * PI / 180;

    Mat srcImg = imread(imgPath);

    int newWidth = (srcImg.cols * cos(radian)) + (srcImg.rows * sin(radian));
    int newHeight = (srcImg.cols * sin(radian)) + (srcImg.rows * cos(radian));

    Mat dstImg(newHeight, newWidth, CV_8UC3, Scalar(0, 0, 0));

    

    for (int row = 0; row < srcImg.rows ; row++)
    {
        for (int col = 0; col < srcImg.cols; col++)
        {
            int x = col - (srcImg.cols / 2);
            int y = row - (srcImg.rows / 2);

            int xPrime = (x * cos(radian)) - (y * sin(radian));
            int yPrime = (x * sin(radian)) + (y * cos(radian));

            int newRow = yPrime + (newHeight / 2); 
            int newCol = xPrime + (newWidth / 2);  

            if (newRow < 0 || newRow >= newHeight)
            {
                continue;
            }
            if (newCol < 0 || newCol >= newWidth)
            {
                continue;
            }

            dstImg.at<Vec3b>(newRow, newCol) = srcImg.at<Vec3b>(row, col); 
        }
    }
    
    // modified의 크기 최적화
    // tran


    namedWindow("ORIGINAL IMAGE", WINDOW_AUTOSIZE);
    imshow("ORIGINAL IMAGE", srcImg);
    namedWindow("MODIFIED IMAGE", WINDOW_AUTOSIZE);
    imshow("MODIFIED IMAGE", dstImg);
    waitKey(0);
    return 0;
}

// const 추가하기 및 최적화
// 리팩터링