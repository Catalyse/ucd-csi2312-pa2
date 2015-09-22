#include "Cluster.h"

namespace Clustering 
{
    // The big three: cpy ctor, overloaded operator=, dtor
    Cluster::Cluster(const Cluster & copy)
    {

    }
    
    Cluster& Cluster::operator=(const Cluster & copy)
    {

    }

    Cluster::~Cluster()
    {

    }

    // Set functions: They allow calling c1.add(c2.remove(p));
    void add(const PointPtr & newPoint)
    {

    }

    const PointPtr &remove(const PointPtr & removePoint)
    {

    }

    // Overloaded operators

    // IO
    std::ostream &operator<<(std::ostream &, const Cluster &); //nope
    std::istream &operator>>(std::istream &, Cluster &);

    // Set-preserving operators (do not duplicate points in the space)
    // - Friends
    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {

    }

    // - Members
    Cluster &Cluster::operator+=(const Cluster &rhs) // union
    {

    }

    Cluster &Cluster::operator-=(const Cluster &rhs) // (asymmetric) difference
    {

    }

    Cluster &Cluster::operator+=(const Point &rhs) // add point
    {

    }

    Cluster &Cluster::operator-=(const Point &rhs) // remove point
    {

    }


    // Set-destructive operators (duplicate points in the space)
    // - Friends
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    {

    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
    {

    }


    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {

    }

    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs)
    {

    }
}

