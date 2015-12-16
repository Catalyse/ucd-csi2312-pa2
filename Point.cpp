#include "Point.h"
#include <sstream>

namespace Clustering
{
    const char Point::POINT_VALUE_DELIM = ',';
    static const int START_INDEX = 1;

    Point::Point()
    {
        dim = 0;
        values = NULL;
    }

    Point::Point(int dimensions)
    {
	   dim = dimensions;
	   values = new double[dimensions + START_INDEX];
	   for(int i = 0 + START_INDEX; i < dimensions + START_INDEX; i++)
	   {
		  values[i] = 0;
	   }
    }

    Point::Point(int dimensions, double * dimensionsArray)
    {
        dim = dimensions;
        values = new double[dimensions + START_INDEX];
        for(int i = 0 + START_INDEX; i < dimensions + START_INDEX; i++)
        {
            values[i] = dimensionsArray[i];
        }
    }

    //Copy Ctor
    Point::Point(const Point & pointToCopy)
    {
	   dim = pointToCopy.getDims();
	   values = new double[dim + START_INDEX];
	   for(int i = 0 + START_INDEX; i < dim + START_INDEX; i++)
	   {
		  values[i] = pointToCopy.getValue(i);
	   }
    }

    Point& Point::operator=(const Point & point)
    {
        if (this == &point)
        {
            return *this;
        }
        else
        {
            dim = point.getDims();
            double* newArray = new double[point.getDims() + START_INDEX];
            for (int i = 0 + START_INDEX; i < point.getDims() + START_INDEX; i++)
            {
                newArray[i] = point.getValue(i);
            }
            delete this->values;
            values = newArray;
        }
        return *this;
    }

    Point::~Point()
    {//Dim deleted with point from stack
        //Caused too many issues.  Would rather have working program and memory leak than everything broke D:!
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
	   for(int i = 0 + START_INDEX; i < dim + START_INDEX; i++)
	   {
		  currentPoint = (comparisonPoint.getValue(i) - values[i]);
           distance += pow(currentPoint, 2);
	   }
	   distance = sqrt(distance);
	   return distance;
    }

    // Overloaded operators

    // Members
    Point &Point::operator*=(double multiple) 
    {
        for (int i = 0 + START_INDEX; i < dim + START_INDEX; i++)
            values[i] *= multiple;
        return *this;
    }
    Point &Point::operator/=(double divisor) 
    {
        if(divisor == 0)
            std::cout << "You cannot divide by Zero" << std::endl;
        else
        {
            for (int i = 0 + START_INDEX; i < dim + START_INDEX; i++)
                values[i] /= divisor;
        }
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
        double temp;
        for(int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++)
        {
            temp = pointA.getValue(i);
            temp += pointB.getValue(i);
            pointA.setValue(i, temp);
        }
	   return pointA;
    }

    Point &operator-=(Point & pointA, const Point & pointB)
    {
        double temp;
        for(int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++)
        {
            temp = pointA.getValue(i);
            temp -= pointB.getValue(i);
            pointA.setValue(i, temp);
        }
	   return pointA;
    }

    const Point operator+(const Point & pointA, const Point & pointB)
    {
        Point sum(pointA.getDims());
        for (int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++) {
            sum.setValue(i, pointA.getValue(i) + pointB.getValue(i));
        }
	    return sum;
    }

    const Point operator-(const Point & pointA, const Point & pointB)
    {
        Point sum(pointA.getDims());
        for (int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++) {
            sum.setValue(i, pointA.getValue(i) + pointB.getValue(i));
        }
        return sum;
    }

    //Roll through vals till I find one thats not equal then return
    bool operator==(const Point & pointA, const Point & pointB)
    {
	   for(int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++)
	   {
		  if(pointA.getValue(i) != pointB.getValue(i))
			 return false;
	   }
	   return true;
    }

    //Roll through vals till I find one thats not equal then return
    bool operator!=(const Point & pointA, const Point & pointB)
    {
	   for(int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++)
	   {
		  if(pointA.getValue(i) != pointB.getValue(i))
			 return true;
	   }
	   return false;
    }
        
    bool operator<(const Point & pointA, const Point & pointB)
    {
	   for(int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++)//The only time this loop should actually iterate is when the two points values are equal.
	   {
		    if(pointA.getValue(i) < pointB.getValue(i))
			    return true;
            if(pointA.getValue(i) > pointB.getValue(i))
                return false;
	   }
	   return false;//If it makes it to this return then they are equal and left !< right
    }

    bool operator>(const Point & pointA, const Point & pointB)
    {
        for(int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++)//The only time this loop should actually iterate is when the two points values are equal.
        {
            if(pointA.getValue(i) > pointB.getValue(i))
                return true;
            if(pointA.getValue(i) < pointB.getValue(i))
                return false;
        }
        return false;//If it makes it to this return then they are equal and left !> right
    }

    bool operator<=(const Point & pointA, const Point & pointB)
    {
        for(int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++)//The only time this loop should actually iterate is when the two points values are equal.
        {
            if(pointA.getValue(i) < pointB.getValue(i))
                return true;
            if(pointA.getValue(i) > pointB.getValue(i))
                return false;
        }
        return true;//If it finished they are equal
    }

    bool operator>=(const Point & pointA, const Point & pointB)
    {
        for(int i = 0 + START_INDEX; i < pointA.getDims() + START_INDEX; i++)//The only time this loop should actually iterate is when the two points values are equal.
        {
            if(pointA.getValue(i) > pointB.getValue(i))
                return true;
            if(pointA.getValue(i) < pointB.getValue(i))
                return false;
        }
        return true;//If it finished they are equal.
    }

    std::ostream &operator<<(std::ostream &stream, const Point &point)
    {
        for(int i = 0 + START_INDEX; i < point.dim + START_INDEX; i++)
        {
            std::cout << point.getValue(i) << " ";
        }
        std::cout << std::endl;

        return stream;
    }

    std::istream &operator>>(std::istream &stream, Point &point)
    {
        std::string value;
        int i = 1;
        double val;

        while (getline(stream, value, ','))
        {
            std::stringstream ss(value);
            ss >> val;
            point.setValue(i, val);
            i++;
        }
        return stream;
    }
}