#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];
    double angle = atof(argv[2]);

    Mat srcImg = imread(imgPath);
    Mat dstImg = imread(imgPath);

    const double PI = 3.1415926;

    for (int x = 0; x < dstImg.rows; x++)
    {
        for (int y = 0; y < dstImg.cols; y++)
        {
            
            // x = (x)(cos)(seta) - (y)(sin)(seta)
            // y = (x)(sin)(seta) + (y)(cos)(seta)


            uint8_t value = dstImg.at<uint8_t>(x, y);

            int xPrime = x * cos(angle * PI / 180) - y * sin(angle * PI / 180);
            int yPrime = x * sin(angle * PI / 180) + y * cos(angle * PI / 180);

            dstImg.at<uint8_t>(xPrime, yPrime) = value;

        }
    }
    
    // print
    imshow(imgPath, srcImg);
    imshow(imgPath, dstImg);
    waitKey(0);

    return 0;
}