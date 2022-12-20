#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];
    double angle = atof(argv[2]);

    Mat img = imread(imgPath);
    namedWindow(imgPath, WINDOW_AUTOSIZE);
    imshow(imgPath, img);
    moveWindow(imgPath, 0, 45);
    waitKey(0);
    destroyAllWindows();

    return 0;
}