#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];
    double angle = atof(argv[2]);

    Mat img = imread(imgPath);
    
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            img.at<uint8_t>(row, col);
        }
    }
    
    imshow(imgPath, img);
    waitKey(0);

    return 0;
}