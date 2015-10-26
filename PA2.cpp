// PA2.cpp : Defines the entry point for the console application.
//

#include "Point.h"
#include <vector>
#include <time.h>
#include <windows.h>

using namespace Clustering;

void GeneratePoint();

int main(void)
{

    GeneratePoint();
    return 0;
}

void GeneratePoint()
{
    double min = 0, max = 100;
    srand(time(NULL));
    int pointSize = rand() % 100;
    std::vector<double> valueArray(pointSize);
    for(int i = 0; i<pointSize; i++)
    {
	   srand(time(NULL));
	   int v1 = min + (rand() % (int)(max - min + 1));
	   Sleep(10);
	   srand(time(NULL));
	   int v2 = min + (rand() % (int)(max - min + 1));
	   double random = (double)v1 / (double)v2;
	   valueArray[i] = random;
    }
    //Point newPoint = Point(pointSize, valueArray);
    //return newPoint;
}
