#include "RotateImg.h"

int main(int argc, char* argv[])
{
    char* imgPath = argv[1];
    double angle = atof(argv[2]);
    double PI = 3.14159265358979323846;
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

    // 2중 for문은 맞는데...
    for (int row = 0; row < srcImg.rows ; row++)
    {
        for (int col = 0; col < srcImg.cols; col++)
        {
            int x = col - (srcImg.cols / 2);
            int y = row - (srcImg.rows / 2);

            double xPrime = (x * cos(radian)) - (y * sin(radian)); //
            double yPrime = (x * sin(radian)) + (y * cos(radian)); //

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

    /*
    for (int row = 0; row < dstImg.rows; row++)
    {
        for (int col = 0; col < dstImg.cols; col++)
        {
            if (dstImg.at<Vec3b>(row, col)[0] == 0 && dstImg.at<Vec3b>(row, col)[1] == 0 && dstImg.at<Vec3b>(row, col)[2] == 0)
            {
                if (row > 0 && row < dstImg.rows - 1 && col > 0 && col < dstImg.cols - 1)
                {
                    uint8_t topB = dstImg.at<Vec3b>(row - 1, col)[0];
                    uint8_t topG = dstImg.at<Vec3b>(row - 1, col)[1];
                    uint8_t topR = dstImg.at<Vec3b>(row - 1, col)[2];
                    
                    uint8_t bottomB = dstImg.at<Vec3b>(row + 1, col)[0];
                    uint8_t bottomG = dstImg.at<Vec3b>(row + 1, col)[1];
                    uint8_t bottomR = dstImg.at<Vec3b>(row + 1, col)[2];
                    
                    uint8_t leftB = dstImg.at<Vec3b>(row, col - 1)[0];
                    uint8_t leftG = dstImg.at<Vec3b>(row, col - 1)[1];
                    uint8_t leftR = dstImg.at<Vec3b>(row, col - 1)[2];

                    uint8_t rightB = dstImg.at<Vec3b>(row, col + 1)[0];
                    uint8_t rightG = dstImg.at<Vec3b>(row, col + 1)[1];
                    uint8_t rightR = dstImg.at<Vec3b>(row, col + 1)[2];

                    uint8_t averageB = (topB + bottomB + leftB + rightB) / 4;
                    uint8_t averageG = (topG + bottomG + leftG + rightG) / 4;
                    uint8_t averageR = (topR + bottomR + leftR + rightR) / 4;

                    dstImg.at<Vec3b>(row, col)[0] = averageB;
                    dstImg.at<Vec3b>(row, col)[1] = averageG;
                    dstImg.at<Vec3b>(row, col)[2] = averageR;
                }
                else if (row == 0 && col == 0) // top left corner
                {
                    uint8_t bottomB = dstImg.at<Vec3b>(row + 1, col)[0];
                    uint8_t bottomG = dstImg.at<Vec3b>(row + 1, col)[1];
                    uint8_t bottomR = dstImg.at<Vec3b>(row + 1, col)[2];

                    uint8_t rightB = dstImg.at<Vec3b>(row, col + 1)[0];
                    uint8_t rightG = dstImg.at<Vec3b>(row, col + 1)[1];
                    uint8_t rightR = dstImg.at<Vec3b>(row, col + 1)[2];

                    uint8_t averageB = (bottomB + rightB) / 2;
                    uint8_t averageG = (bottomG + rightG) / 2;
                    uint8_t averageR = (bottomR + rightR) / 2;

                    dstImg.at<Vec3b>(row, col)[0] = averageB;
                    dstImg.at<Vec3b>(row, col)[1] = averageG;
                    dstImg.at<Vec3b>(row, col)[2] = averageR;
                }
                else if (row == 0 && col == dstImg.cols - 1) // top right corner
                {
                    uint8_t bottomB = dstImg.at<Vec3b>(row + 1, col)[0];
                    uint8_t bottomG = dstImg.at<Vec3b>(row + 1, col)[1];
                    uint8_t bottomR = dstImg.at<Vec3b>(row + 1, col)[2];

                    uint8_t leftB = dstImg.at<Vec3b>(row, col - 1)[0];
                    uint8_t leftG = dstImg.at<Vec3b>(row, col - 1)[1];
                    uint8_t leftR = dstImg.at<Vec3b>(row, col - 1)[2];

                    uint8_t averageB = (bottomB + leftB) / 2;
                    uint8_t averageG = (bottomG + leftG) / 2;
                    uint8_t averageR = (bottomR + leftR) / 2;

                    dstImg.at<Vec3b>(row, col)[0] = averageB;
                    dstImg.at<Vec3b>(row, col)[1] = averageG;
                    dstImg.at<Vec3b>(row, col)[2] = averageR;
                }
                else if (row == dstImg.rows - 1 && col == 0) // bottom left corner
                {
                    uint8_t topB = dstImg.at<Vec3b>(row - 1, col)[0];
                    uint8_t topG = dstImg.at<Vec3b>(row - 1, col)[1];
                    uint8_t topR = dstImg.at<Vec3b>(row - 1, col)[2];

                    uint8_t rightB = dstImg.at<Vec3b>(row, col + 1)[0];
                    uint8_t rightG = dstImg.at<Vec3b>(row, col + 1)[1];
                    uint8_t rightR = dstImg.at<Vec3b>(row, col + 1)[2];

                    uint8_t averageB = (topB + rightB) / 2;
                    uint8_t averageG = (topG + rightG) / 2;
                    uint8_t averageR = (topR + rightR) / 2;

                    dstImg.at<Vec3b>(row, col)[0] = averageB;
                    dstImg.at<Vec3b>(row, col)[1] = averageG;
                    dstImg.at<Vec3b>(row, col)[2] = averageR;
                }
                else if (row == dstImg.rows - 1 && col == dstImg.cols - 1) // bottom right corner
                {
                    uint8_t topB = dstImg.at<Vec3b>(row - 1, col)[0];
                    uint8_t topG = dstImg.at<Vec3b>(row - 1, col)[1];
                    uint8_t topR = dstImg.at<Vec3b>(row - 1, col)[2];

                    uint8_t leftB = dstImg.at<Vec3b>(row, col - 1)[0];
                    uint8_t leftG = dstImg.at<Vec3b>(row, col - 1)[1];
                    uint8_t leftR = dstImg.at<Vec3b>(row, col - 1)[2];

                    uint8_t averageB = (topB + leftB) / 2;
                    uint8_t averageG = (topG + leftG) / 2;
                    uint8_t averageR = (topR + leftR) / 2;

                    dstImg.at<Vec3b>(row, col)[0] = averageB;
                    dstImg.at<Vec3b>(row, col)[1] = averageG;
                    dstImg.at<Vec3b>(row, col)[2] = averageR;
                }
                else if (row > 0 && row < dstImg.rows - 1 && col == 0) // left side
                {
                    uint8_t topB = dstImg.at<Vec3b>(row - 1, col)[0];
                    uint8_t topG = dstImg.at<Vec3b>(row - 1, col)[1];
                    uint8_t topR = dstImg.at<Vec3b>(row - 1, col)[2];

                    uint8_t bottomB = dstImg.at<Vec3b>(row + 1, col)[0];
                    uint8_t bottomG = dstImg.at<Vec3b>(row + 1, col)[1];
                    uint8_t bottomR = dstImg.at<Vec3b>(row + 1, col)[2];

                    uint8_t rightB = dstImg.at<Vec3b>(row, col + 1)[0];
                    uint8_t rightG = dstImg.at<Vec3b>(row, col + 1)[1];
                    uint8_t rightR = dstImg.at<Vec3b>(row, col + 1)[2];

                    uint8_t averageB = (topB + bottomB + rightB) / 3;
                    uint8_t averageG = (topG + bottomG + rightG) / 3;
                    uint8_t averageR = (topR + bottomR + rightR) / 3;

                    dstImg.at<Vec3b>(row, col)[0] = averageB;
                    dstImg.at<Vec3b>(row, col)[1] = averageG;
                    dstImg.at<Vec3b>(row, col)[2] = averageR;
                }
                else if (row > 0 && row < dstImg.rows && col == dstImg.cols - 1) // right side
                {
                    uint8_t topB = dstImg.at<Vec3b>(row - 1, col)[0];
                    uint8_t topG = dstImg.at<Vec3b>(row - 1, col)[1];
                    uint8_t topR = dstImg.at<Vec3b>(row - 1, col)[2];

                    uint8_t bottomB = dstImg.at<Vec3b>(row + 1, col)[0];
                    uint8_t bottomG = dstImg.at<Vec3b>(row + 1, col)[1];
                    uint8_t bottomR = dstImg.at<Vec3b>(row + 1, col)[2];

                    uint8_t leftB = dstImg.at<Vec3b>(row, col - 1)[0];
                    uint8_t leftG = dstImg.at<Vec3b>(row, col - 1)[1];
                    uint8_t leftR = dstImg.at<Vec3b>(row, col - 1)[2];

                    uint8_t averageB = (topB + bottomB + leftB) / 3;
                    uint8_t averageG = (topG + bottomG + leftG) / 3;
                    uint8_t averageR = (topR + bottomR + leftR) / 3;

                    dstImg.at<Vec3b>(row, col)[0] = averageB;
                    dstImg.at<Vec3b>(row, col)[1] = averageG;
                    dstImg.at<Vec3b>(row, col)[2] = averageR;
                }
                else if (col > 0 && col < dstImg.cols - 1 && row == 0) // top side
                {
                    uint8_t bottomB = dstImg.at<Vec3b>(row + 1, col)[0];
                    uint8_t bottomG = dstImg.at<Vec3b>(row + 1, col)[1];
                    uint8_t bottomR = dstImg.at<Vec3b>(row + 1, col)[2];

                    uint8_t leftB = dstImg.at<Vec3b>(row, col - 1)[0];
                    uint8_t leftG = dstImg.at<Vec3b>(row, col - 1)[1];
                    uint8_t leftR = dstImg.at<Vec3b>(row, col - 1)[2];

                    uint8_t rightB = dstImg.at<Vec3b>(row, col + 1)[0];
                    uint8_t rightG = dstImg.at<Vec3b>(row, col + 1)[1];
                    uint8_t rightR = dstImg.at<Vec3b>(row, col + 1)[2];

                    uint8_t averageB = (bottomB + leftB + rightB) / 3;
                    uint8_t averageG = (bottomG + leftG + rightG) / 3;
                    uint8_t averageR = (bottomR + leftR + rightR) / 3;

                    dstImg.at<Vec3b>(row, col)[0] = averageB;
                    dstImg.at<Vec3b>(row, col)[1] = averageG;
                    dstImg.at<Vec3b>(row, col)[2] = averageR;
                }
                else if (col > 0 && col < dstImg.cols - 1 && row == dstImg.rows -1 ) // bottom side
                {
                    uint8_t topB = dstImg.at<Vec3b>(row - 1, col)[0];
                    uint8_t topG = dstImg.at<Vec3b>(row - 1, col)[1];
                    uint8_t topR = dstImg.at<Vec3b>(row - 1, col)[2];

                    uint8_t leftB = dstImg.at<Vec3b>(row, col - 1)[0];
                    uint8_t leftG = dstImg.at<Vec3b>(row, col - 1)[1];
                    uint8_t leftR = dstImg.at<Vec3b>(row, col - 1)[2];

                    uint8_t rightB = dstImg.at<Vec3b>(row, col + 1)[0];
                    uint8_t rightG = dstImg.at<Vec3b>(row, col + 1)[1];
                    uint8_t rightR = dstImg.at<Vec3b>(row, col + 1)[2];

                    uint8_t averageB = (topB + leftB + rightB) / 3;
                    uint8_t averageG = (topG + leftG + rightG) / 3;
                    uint8_t averageR = (topR + leftR + rightR) / 3;

                    dstImg.at<Vec3b>(row, col)[0] = averageB;
                    dstImg.at<Vec3b>(row, col)[1] = averageG;
                    dstImg.at<Vec3b>(row, col)[2] = averageR;
                }
            }
        }
    }
    */

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