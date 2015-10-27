// PA2.cpp : Defines the entry point for the console application.
//

#include "Point.h"
#include "Cluster.h"
#include <vector>
#include <time.h>
#include <windows.h>

using namespace Clustering;

void GeneratePoint();
void Test();

int main(void)
{
    Test();
    //GeneratePoint();
    return 0;
}

void Test()
{
    PointPtr p1 = new Point(3);
    p1->setValue(0, 4);
    p1->setValue(1, 5);
    p1->setValue(2, 6);

    PointPtr p2 = new Point(3);
    p2->setValue(0, 7);
    p2->setValue(1, 8);
    p2->setValue(2, 9);

    PointPtr p4 = new Point(3);
    p4->setValue(0, 1);
    p4->setValue(1, 1);
    p4->setValue(2, 1);

    PointPtr p5 = new Point(3);
    p5->setValue(0, 2);
    p5->setValue(1, 2);
    p5->setValue(2, 2);

    PointPtr p6 = new Point(3);
    p6->setValue(0, 3);
    p6->setValue(1, 3);
    p6->setValue(2, 3);

    PointPtr p3 = new Point(3);

    std::cout << "P1 has " << p1->getDims() << " Dimensions " << std::endl;


    *p3 = *p1 + *p2;

    std::cout << "P1 output: " << std::endl;
    std::cout << *p1;
    std::cout << "P2 output: " << std::endl;
    std::cout << *p2;
    std::cout << "P3 output: " << std::endl;
    std::cout << *p3;

    Cluster c1;

    c1.add(p1);
    c1.add(p2);
    c1.add(p3);
    c1.add(p4);
    c1.add(p5);
    c1.add(p6);
    //c1.remove(p1);

    std::cout << "Cluster output: " << std::endl;
    std::cout << c1;
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
