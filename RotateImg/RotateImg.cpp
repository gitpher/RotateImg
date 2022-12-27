#include "RotateImg.h"

double getRadian(double angle)
{
    return angle * PI / 180;
}

Mat createDstImg(Mat& srcImg, double angle)
{
    double radian;
    
    int cnt = abs(angle / 90);
    for (int i = 0; i < cnt; i++)
    {
        (angle > 0) ? angle -= 90 : angle += 90;
    }

    radian = getRadian(angle);

	int dstRow = (srcImg.cols * sin(radian)) + (srcImg.rows * cos(radian));
	int dstCol = (srcImg.cols * cos(radian)) + (srcImg.rows * sin(radian));

	Mat dstImg(dstRow, dstCol, CV_8UC3, Scalar(0, 0, 0));

	return dstImg;
}

void fillDstImg(Mat& dstImg, Mat& srcImg, double radian)
{
    for (int dstRow = 0; dstRow < dstImg.rows; dstRow++)
    {
        for (int dstCol = 0; dstCol < dstImg.cols; dstCol++)
        {
            // dstRow = 0, dstCol = 0


            double x = dstCol - (dstImg.cols / 2);
            double y = dstRow - (dstImg.rows / 2);

            double xP = (x * cos(radian)) + (y * sin(radian)); 
            double yP = ((-x) * sin(radian)) + (y * cos(radian)); 

            double srcRow = yP + (srcImg.rows / 2);
            double srcCol = xP + (srcImg.cols / 2);

            if (dstCol == 0)
            {
                cout << "dstRow: " << dstRow << ", " << "srcRow: " << srcRow << ", srcCol: " << srcCol << endl;
                /*uchar B = srcImg.at<Vec3b>(srcRow, srcCol)[0];
                uchar G = srcImg.at<Vec3b>(srcRow, srcCol)[1];
                uchar R = srcImg.at<Vec3b>(srcRow, srcCol)[2];
                cout << "BGR: " << B << G << R << endl;*/
            }//

            if (isOutOfBounds(dstImg, srcImg, dstRow, dstCol, srcRow-1, srcCol)) //  -1
            {
                continue;
            }

            interpolateDstImg(dstImg, srcImg, dstRow, dstCol, srcRow-1, srcCol); //  -1
        }
    }
}

bool isOutOfBounds(Mat& dstImg, Mat& srcImg, int dstRow, int dstCol, float srcRow, float srcCol)
{
    if (srcRow < 0 || srcRow > srcImg.rows - 1)
    {
        return true;
    }
    if (srcCol < 0 || srcCol > srcImg.cols - 1)
    {
        return true;
    }
    return false;
}

void interpolateDstImg(Mat& dstImg, Mat& srcImg, int dstRow, int dstCol, double srcRow, double srcCol)
{
    for (int i = 0; i < 3; i++)
    {
        //// row만 넘어가도 col까지 끝 값을 준다
        //if (srcRow == srcImg.rows - 1 || srcCol == srcImg.cols - 1)
        //{
        //    dstImg.at<Vec3b>(dstRow, dstCol)[i] = srcImg.at<Vec3b>(srcRow, srcCol)[i];
        //}
        //else
        //{
            double weightHorizontal = srcCol - floor(srcCol);
            double weightVertical = srcRow - floor(srcRow);

            uchar pxRef = srcImg.at<Vec3b>((int)srcRow, (int)srcCol)[i];
            uchar pxToTheRight = srcImg.at<Vec3b>((int)srcRow, (int)srcCol + 1)[i];
            uchar pxToTheBottom = srcImg.at<Vec3b>((int)srcRow + 1, (int)srcCol)[i];
            uchar pxToTheRightDiagonal = srcImg.at<Vec3b>((int)srcRow + 1, (int)srcCol + 1)[i];

            uchar pxCentre = (pxRef * (1 - weightVertical) + pxToTheBottom * weightVertical) * (1 - weightHorizontal)
                + (pxToTheRight * (1 - weightVertical) + pxToTheRightDiagonal * weightVertical) * weightHorizontal;

            dstImg.at<Vec3b>(dstRow, dstCol)[i] = pxCentre;
        /*}*/
    }
}

void displayImage(Mat& image, string displayName)
{
	namedWindow(displayName, WINDOW_AUTOSIZE);
	imshow(displayName, image);
}