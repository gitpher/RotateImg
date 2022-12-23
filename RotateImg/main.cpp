#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];
    double angle = atof(argv[2]);

    double PI = 3.14159265358979323846; // 나중에 cmath PI로 대체
    double radian = angle * PI / 180;

    Mat srcImg = imread(imgPath);

    if (srcImg.empty())
    {
        cout << "THERE IS NO IMAGE" << endl;
        return 1;
    }

    double srcImg_h = srcImg.rows;
    double srcImg_w = srcImg.cols;

    double dstImg_h = (srcImg.cols * sin(radian)) + (srcImg.rows * cos(radian));
    double dstImg_w = (srcImg.cols * cos(radian)) + (srcImg.rows * sin(radian));
    
    Mat dstImg(dstImg_h, dstImg_w, CV_8UC3, Scalar(0, 0, 0)); 

    for (int h = 0; h < dstImg_h; h++)
    {
        for (int w = 0; w < dstImg_w; w++)
        {
            double x = w - (dstImg_w / 2);
            double y = h - (dstImg_h / 2);
            
            double xP = (x * cos(radian)) + (y * sin(radian));
            double yP = ((-x) * sin(radian)) + (y * cos(radian));

            double row = yP + (srcImg_h / 2);
            double col = xP + (srcImg_w / 2);

            // if문 나중에 단순화 / 리팩터링
            if (row < 0 || row > srcImg_h - 1)
            {
                continue;
            }
            if (col < 0 || col > srcImg_w - 1)
            {
                continue;
            }
            if (h < 0 || h > dstImg_h - 1)
            {
                continue;
            }
            if (w < 0 || w > dstImg_w - 1)
            {
                continue;
            }

            
            
            

            dstImg.at<Vec3b>(h, w) = srcImg.at<Vec3b>(row, col);
        }
    }

    displayImage(srcImg, "ORIGINAL IMAGE");
    displayImage(dstImg, "ROTATED IMAGE");
    waitKey(0);
    
    return 0;
}