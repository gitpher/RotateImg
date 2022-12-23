#include "RotateImg.h"

void displayImage(Mat& image, string name) // 나중에 name 어떻게 바꿀지 정하기
{
	namedWindow(name, WINDOW_AUTOSIZE);
	imshow(name, image);
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
