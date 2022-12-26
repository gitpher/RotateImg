#include "RotateImg.h"

int main(int argc, char* argv[])
{
    const char* const imgPath = argv[1];
    const double angle = atof(argv[2]);

    const double PI = 3.14159265358979323846;
    const double radian = angle * PI / 180;

    Mat srcImg = imread(imgPath);

    if (imgPath == NULL || srcImg.empty())
    {
        cout << "*** THERE IS NO IMAGE (PLEASE CHECK IF THE IMAGE IS VALID) ***" << endl;
        return 1;
    }

    Mat dstImg = createDstImg(srcImg, radian);
    fillDstImg(dstImg, srcImg, radian);

    displayImage(srcImg, "ORIGINAL IMAGE");
    displayImage(dstImg, "ROTATED IMAGE");
    waitKey(0);
    return 0;
}