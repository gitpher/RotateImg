#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];
    double angle = atof(argv[2]);

    double PI = 3.1415926;
    double radian = angle * PI / 180;

    Mat srcImg = imread(imgPath);

    // 이미지 있는지 검사
    if (srcImg.empty())
    {
        cout << "THERE IS NO IMAGE" << endl;
        return 1;
    }

    int newWidth = (srcImg.cols * cos(radian)) + (srcImg.rows * sin(radian));
    int newHeight = (srcImg.cols * sin(radian)) + (srcImg.rows * cos(radian));

    Mat dstImg(newHeight, newWidth, CV_8UC3, Scalar(0, 0, 0)); // interpolation 때문에 여기를 나중에 바꿔야 할 수도

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

            if (newRow < 0 || newRow > newHeight - 1)
            {
                continue;
            }
            if (newCol < 0 || newCol > newWidth - 1)
            {
                continue;
            }

            dstImg.at<Vec3b>(newRow, newCol) = srcImg.at<Vec3b>(row, col); 
        }
    }
    
    cout << "*************************" << dstImg.at<Vec3b>(0, 0) << endl;
    cout << "*************************" << dstImg.at<Vec3b>(dstImg.rows - 1, 0) << endl;
    cout << "*************************" << dstImg.at<Vec3b>(0, dstImg.cols - 1) << endl;

    cout << endl;

    cout << "*************************" << dstImg.at<Vec3b>(0, 0)[0] << endl;
    cout << "*************************" << dstImg.at<Vec3b>(0, 0)[1] << endl;
    cout << "*************************" << dstImg.at<Vec3b>(0, 0)[2] << endl;


    for (int row = 0; row < dstImg.rows; row++)
    {
        for (int col = 0; col < dstImg.cols; col++)
        {
            if (dstImg.at<Vec3b>(row, col)[0] == 0 && dstImg.at<Vec3b>(row, col)[1] == 0 && dstImg.at<Vec3b>(row, col)[2] == 0)
            {
                if (col < dstImg.cols - 1)
                {
                    dstImg.at<Vec3b>(row, col)[0] = dstImg.at<Vec3b>(row, col + 1)[0];
                    dstImg.at<Vec3b>(row, col)[1] = dstImg.at<Vec3b>(row, col + 1)[1];
                    dstImg.at<Vec3b>(row, col)[2] = dstImg.at<Vec3b>(row, col + 1)[2];
                }
            }
        }
    }



    namedWindow("ORIGINAL IMAGE", WINDOW_AUTOSIZE);
    imshow("ORIGINAL IMAGE", srcImg);
    namedWindow("MODIFIED IMAGE", WINDOW_AUTOSIZE);
    imshow("MODIFIED IMAGE", dstImg);
    waitKey(0);
    return 0;
}


// 90도시 이미지 밀림 현상
// 구멍 숭숭

// 180 이상의 각도를 입력하면 에러남 
// const 추가하기 및 최적화
// 리팩터링