// PA2.cpp : Defines the entry point for the console application.
//

#include "Point.h"
#include <vector>

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
    int pointSize = rand() % 100;
    std::vector<double> valueArray(pointSize);
    for(int i = 0; i<pointSize; i++)
    {
	   int v1 = rand() %100;
	   int v2 = rand() %100;
	   double random = (double)v1 / (double)v2;
	   valueArray[i] = random;
    }
    //Point newPoint = Point(pointSize, valueArray);
    //return newPoint;
}
