#include "RotateImg.h"

int main(int argc, char* argv[])
{
    const char* const imagePath = argv[1];
    const double angle = atof(argv[2]);
    const double PI = 3.14159265358979323846;
    const double radian = angle * PI / 180;

    Mat sourceImage = imread(imagePath);

    if (sourceImage.empty())
    {
        cout << "THERE IS NO IMAGE" << endl;
        return 1;
    }

    int destinationImageWidth = (sourceImage.cols * cos(radian)) + (sourceImage.rows * sin(radian));
    int destinationImageHeight = (sourceImage.cols * sin(radian)) + (sourceImage.rows * cos(radian));

    Mat destinationImage(destinationImageHeight, destinationImageWidth, CV_8UC3, Scalar(0, 0, 0)); 

    for (int row = 0; row < destinationImageHeight; row++)
    {
        for (int col = 0; col < destinationImageWidth; col++)
        {
            /* destinationImage의 반만큼 왼쪽과 위로 올리기 */
            double x = col - (destinationImageWidth / 2);
            double y = row - (destinationImageHeight / 2);
            
            /* 역행렬 */ 
            double xPrime = (x * cos(radian)) + (y * sin(radian));
            double yPrime = ((-x) * sin(radian)) + (y * cos(radian));

            /* destinationImage의 반만큼 오른쪽과 아래로 내리기 */
            double newRow = yPrime + (sourceImage.rows / 2); //
            double newCol = xPrime + (sourceImage.cols / 2); //

            if (newRow < 0 || newRow > sourceImage.rows - 1)
            {
                continue;
            }
            if (newCol < 0 || newCol > sourceImage.cols - 1)
            {
                continue;
            }
            if (row < 0 || row > destinationImageHeight - 1)
            {
                continue;
            }
            if (col < 0 || col > destinationImageWidth - 1)
            {
                continue;
            }

            destinationImage.at<Vec3b>(row, col) = sourceImage.at<Vec3b>(newRow, newCol);
        }
    }

    displayImage(sourceImage, "ORIGINAL IMAGE");
    displayImage(destinationImage, "ROTATED IMAGE");
    waitKey(0);
    
    return 0;
}