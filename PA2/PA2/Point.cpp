#include "Point.h"

namespace Clustering
{
    Point::Point(int dimensions)
    {
	   values = new double[dimensions];
	   for(int i = 0; i < dimensions; i++)
	   {
		  values[i] = 0;
	   }
    }

    Point::Point(int dimensions, double * dimensionsArray)
    {
	   values = new double[dimensions];
	   for(int i = 0; i < dimensions; i++)
	   {
		  values[i] = dimensionsArray[i];
	   }
    }

    // Big three: cpy ctor, overloaded operator=, dtor
    Point::Point(const Point & pointToCopy)
    {
	   dim = pointToCopy.dim;
	   values = new double[dim];
	   for(int i = 0; i < dim; i++)
	   {
		  values[i] = pointToCopy.values[i];
	   }
    }

    Point& Point::operator=(const Point & copy)
    {
	   Point newPoint = Point(copy.dim, copy.values);
	   return newPoint;
    }

    Point::~Point()
    {//Dim deleted with point from stack
	   delete values;
    }

    // Accessors & mutators

    void Point::setValue(int point, double value)
    {
	   values[point] = value;
    }
    double Point::getValue(int point) const
    {
	   return values[point];
    }


    // Functions
    double Point::distanceTo(const Point & comparisonPoint) const
    {
	   double distance = 0.0;
	   double currentPoint = 0.0;
	   for(int i = 0; i < dim; i++)
	   {
		  currentPoint = values[i] - comparisonPoint.values[i];
		  currentPoint = pow(currentPoint, 2);
		  distance+= currentPoint;
	   }
	   distance = sqrt(distance);
	   return distance;
    }

    // Overloaded operators

    // Members

    Point &Point::operator*=(double multiple) 
    {
        for (int i = 0; i < dim; i++)
            values[i] *= multiple;
        return *this;
    }
    Point &Point::operator/=(double divisor) 
    {
        for (int i = 0; i < dim; i++)
            values[i] /= divisor;
        return *this;
    }
    const Point Point::operator*(double multiple) const 
    {
        return Point(dim, values) *= multiple;
    }
    const Point Point::operator/(double divisor) const 
    {
        return Point(dim, values) /= divisor;
    }

    //Friends
    Point &operator+=(Point & pointA, const Point & pointB)
    {
	   for(int i = 0; i < pointA.dim; i++)
	   {
		  pointA.values[i] += pointB.values[i]; 
	   }
	   return pointA;
    }

    Point &operator-=(Point & pointA, const Point & pointB)
    {
	   for(int i = 0; i < pointA.dim; i++)
	   {
		  pointA.values[i] -= pointB.values[i]; 
	   }
	   return pointA;
    }

    const Point operator+(const Point &, const Point &)
    {

    }

    const Point operator-(const Point &, const Point &)
    {

    }
        
    bool operator==(const Point &, const Point &);
    bool operator!=(const Point &, const Point &);
        
    bool operator<(const Point &, const Point &);
    bool operator>(const Point &, const Point &);
    bool operator<=(const Point &, const Point &);
    bool operator>=(const Point &, const Point &);

    std::ostream &operator<<(std::ostream &, const Point &);
    std::istream &operator>>(std::istream &, Point &);
}