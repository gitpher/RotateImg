#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];

    cv::Mat img = cv::imread(imgPath);
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}