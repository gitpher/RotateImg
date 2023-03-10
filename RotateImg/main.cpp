#include "RotateImg.h"

int main(int argc, char* argv[])
{
    const char* const imgPath = argv[1];
    const double angle = atof(argv[2]);
    const double radian = getRadian(angle);

    Mat srcImg = imread(imgPath);

    if (imgPath == NULL || srcImg.empty())
    {
        cout << "*** ERROR: NO IMAGE (PLEASE CHECK IF THE IMAGE IS VALID) ***" << endl;
        return 1;
    }

    Mat dstImg = createDstImg(srcImg, angle);

    Mat filledDstImg = fillDstImg(dstImg, srcImg, radian);

    displayImage(srcImg, "ORIGINAL IMAGE");
    displayImage(filledDstImg, "ROTATED IMAGE");
    waitKey(0);

    return 0;
}