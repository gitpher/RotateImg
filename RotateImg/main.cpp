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

    std::cerr << "Num src pixels: " << srcImg.rows * srcImg.cols << std::endl;

    Mat dstImg = createDstImg(srcImg, angle);

    int64 tic = getTickCount();
    fillDstImg(dstImg, srcImg, radian);
    std::cerr << "Elapsed time for fillDstImg(): " << (getTickCount() - tic) / getTickFrequency() * 1000 << " ms" << std::endl;
    // tic = getTickCount();
    // fillDstImg2(dstImg, srcImg, radian);
    // std::cerr << "Elapsed time for fillDstImg2(): " << (getTickCount() - tic) / getTickFrequency() * 1000 << " ms" << std::endl;

    displayImage(srcImg, "ORIGINAL IMAGE");
    displayImage(dstImg, "ROTATED IMAGE");
    waitKey(0);
    return 0;
}