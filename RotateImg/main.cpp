#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];
    double angle = atof(argv[2]);

    Mat srcImg = imread(imgPath);
    Mat dstImg = imread(imgPath);


    for (int r = 0; r < dstImg.rows; r++)
    {
        for (int c = 0; c < dstImg.cols; c++)
        {
            
            // x = (x)(cos)(seta) - (y)(sin)(seta)
            // y = (x)(sin)(seta) + (y)(cos)(seta)
            dstImg.at<uint8_t>(r, c);
        }
    }
    
    // print
    imshow(imgPath, srcImg);
    imshow(imgPath, dstImg);
    waitKey(0);

    return 0;
}