// PA2.cpp : Defines the entry point for the console application.
//

#include "Point.h"
#include "Cluster.h"
#include <vector>
#include <time.h>
#include <windows.h>

using namespace Clustering;

void GeneratePoint(PointPtr, int);
void Test();

int main(void)
{
    srand(time(NULL));
    //Test();
    double min = 0, max = 100;
    int pointCount = min + (rand() % (int)(max - min + 1));
    //int pointDims = min + (rand() % (int)(max - min + 1));
    int pointDims = 5;
    Cluster c1;
    for(int i = 0; i<pointCount;i++) //Generate and fill points
    {
        PointPtr newPoint = new Point(pointDims);
        GeneratePoint(newPoint, pointDims);
        c1.add(newPoint);
    }

    std::cout << "Cluster output: " << std::endl;
    std::cout << c1;
    return 0;
}

void Test()
{
}

void GeneratePoint(PointPtr point, int pointSize)
{
    double min = 50, max = 100;
    for(int i = 0; i<pointSize; i++)
    {
	    int v1 = min + (rand() % (int)(max + min));
	    int v2 = (rand() % 5 + 1);
	    double random = (double)v1 / (double)v2;
        point->setValue(i, random);
    }
}
