#include "RotateImg.h"


#include "RotateImg.h"

int main(int argc, char* argv[])
{

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    double angle = atof(argv[3]);
    double PI = 3.14159265358979323846;
    double radian = angle * PI / 180;

    double xPrime = (x * cos(radian)) - (y * sin(radian));
    double yPrime = (x * sin(radian)) + (y * cos(radian)); 

    cout << "(" << xPrime << ", " << yPrime << ")" << endl;
    cout << "(" << (int)(xPrime + 0.5) << ", " << (int)(yPrime + 0.5) << ")" << endl;
}