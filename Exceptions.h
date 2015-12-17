#ifndef CLUSTERING_EXCEPTIONS_H
#define CLUSTERING_EXCEPTIONS_H

#include <string>
#include <iostream>

#include "Cluster.h"

using namespace std;

namespace Clustering
{
    class DimensionalityMismatchEx
    {
    private:
        string name = "Dimensionality Mismatch Error: ";
        string message;
    public:
        // Constructors
        DimensionalityMismatchEx(string);

        // Getters
        string getName() {return this->name;}
        string getErr() {return this->message;}

        friend std::ostream &operator<<(ostream &, DimensionalityMismatchEx &);

    };

    class OutOfBoundsEx
    {

    private:
        string name = "Out Of Bounds Error: ";
        string message;
    public:
        OutOfBoundsEx(string);

        string getName() {return this->name;};
        string getError() {return this->message;};

        friend std::ostream &operator<<(ostream &, OutOfBoundsEx &);
    };

    class RemoveFromEmptyEx
    {
    private:
        string name = "Remove From Empty Error: ";
        string message;
    public:
        RemoveFromEmptyEx(string);

        string getName() {return this->name;};
        string getErr() {return this->message;};


        friend std::ostream &operator<<(ostream &, RemoveFromEmptyEx &);
    };
}


#endif //CLUSTERING_EXCEPTIONS_H
