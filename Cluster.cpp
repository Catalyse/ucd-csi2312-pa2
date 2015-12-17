#include "Cluster.h"
#include <sstream>
#include <algorithm> //For counting

namespace Clustering 
{
    const char Cluster::POINT_CLUSTER_ID_DELIM = ':';
    unsigned int Cluster::__idGenerator = 0;

    // The big three: cpy ctor, overloaded operator=, dtor
    Cluster::Cluster(const Cluster & copy) : __centroid(copy.getDimensionality())
    {
        if (this != &copy)
        {
            this->__size = 0;
            this->__dimensionality = copy.__dimensionality;
            this->__points = nullptr;
            this->__release_points = copy.__release_points;
            this->__greedy = copy.__greedy;
            this->__id = copy.getId();
            LNodePtr current;
            for (current = copy.__points; current != nullptr; current = current->next)
            {
                this->add(current->p);
            }
        }
        else
        {
            //dont copy self.
        }
    }

    Cluster &Cluster::operator=(const Cluster & copy)
    {
        if (this != &copy)
        {
            this->__size = 0;
            this->__id = copy.getId();
            for (LNodePtr current = this->__points; current != nullptr; )
            {
                delete current->p;
                LNodePtr last = current;
                current=current->next;
                delete last;
            }
            for (int i = 0; i < copy.getSize(); i++)
            {
                this->add(copy[i]);
            }
        }
        else
        {
            return *this;
        }
    }

    Cluster::~Cluster()
    {//Was causing too many issues, leaving blank for now

    }

    //Centroid methods
    void Cluster::computeCentroid()
    {
        PointPtr centroid = new Point(this->__dimensionality);
        for (LNodePtr current = this->__points; current != nullptr; current = current->next)
        {
            *centroid += *current->p;
        }
        *centroid /= this->getSize();
        this->setCentroid(*centroid);
    }

    //kmeans methods
    void Cluster::pickPoints(unsigned int pick, PointPtr * pointArray)
    {
        LNodePtr current = this->__points;
        for (int i = 0; i < pick; i++)
        {
            if (current != nullptr)
            {
                pointArray[i] = current->p;
                current = current->next;
            }
            else
            {
                Point * point = new Point(this->__dimensionality);
                for (int i = 1; i < this->__dimensionality + 1; i++)
                {
                    point->setValue(i, std::numeric_limits<double>::max());
                }
                pointArray[i] = point;
            }
        }
    }

    double Cluster::intraClusterDistance() const
    {
        double sum = 0;
        LNodePtr current1 = this->__points;
        for (current1; current1 != nullptr; current1 = current1->next)
        {
            LNodePtr current2 = this->__points;
            for (current2; current2 != nullptr; current2 = current2->next)
            {
                sum += current1->p->distanceTo(*current2->p);
            }
        }
        return (sum / 2.0);
    }

    int Cluster::getClusterEdges() const
    {
        return ((this->__size * (this->__size - 1)) / 2);
    }


    double interClusterDistance(const Cluster &clusterA, const Cluster &clusterB)
    {
        Cluster cluster1(clusterA);
        Cluster cluster2(clusterB);
        double sum = 0;
        LNodePtr current1 = cluster1.__points;
        for (current1; current1 != nullptr; current1 = current1->next)
        {
            LNodePtr current2 = cluster2.__points;
            for (current2; current2 != nullptr; current2 = current2->next)
            {
                sum += current1->p->distanceTo(*current2->p);
            }
        }
        if (cluster1.__size > 1){
            sum /= 2;
        }
        return sum;
    }
    // Same thing as (getClusterEdges), but between two __clusters.
    int interClusterEdges(const Cluster &c1, const Cluster &c2)
    {
        Cluster cluster1(c1);
        Cluster cluster2(c2);
        double edges = cluster1.getSize() * cluster2.getSize();
        return edges;
    }

    bool Cluster::contains(const PointPtr &find) const
    {
        LNodePtr current;
        for (current = this->__points; current != nullptr; current = current->next)
        {
            if (current->p == find)
            {
                return true;
            }
        }
        return false;
    }

    // Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const PointPtr &newPoint)
    {
        if(__dimensionality != 0 && newPoint->getDims() != __dimensionality)
        {
            //std::cout << "Invalid Point: Cannot add different sized points to a cluster!" << std::endl;
        }
        else
        {
            LNodePtr node = new LNode(nullptr, nullptr);

            if (__points == nullptr)
            {
                __points = node;
                __points->p = newPoint;
                node->next = nullptr;
                __dimensionality = newPoint->getDims();//Set our Clusters point size type when the first element is added.
            }
            else
            {
                LNodePtr current = __points;
                PointPtr currentPoint = __points->p;

                if (*newPoint > *currentPoint || *newPoint == *currentPoint)
                {
                    __points = node;
                    node->p = newPoint;
                    node->next = current;
                }
                else
                {
                    while (current != nullptr)
                    {
                        LNodePtr nextNode = current->next;
                        if (nextNode != nullptr)
                        {
                            PointPtr nextPoint = nextNode->p;

                            if (*newPoint >= *nextPoint)//We found where to put it
                            {
                                current->next = node;
                                node->p = newPoint;
                                node->next = nextNode;
                                break;
                            }
                            else if (current->next != nullptr) //move to the next val
                            {
                                current = nextNode;
                                currentPoint = nextPoint;
                            }
                        }
                        else
                        {
                            current->next = node;
                            current->next->p = newPoint;
                            break;
                        }
                    }
                }
            }
            __size++;
        }
    }

    const PointPtr &Cluster::remove(const PointPtr & removePoint)
    {
        if(__points != nullptr)
        {
            LNodePtr current;
            LNodePtr last = nullptr;
            for (current = this->__points; current != nullptr; current = current->next)
            {
                if (current->p == removePoint)
                {
                    if (last == nullptr)
                    {
                        this->__points = this->__points->next;
                        --(this->__size);
                        break;
                    }
                    else
                    {
                        last->next = current->next;
                        --(this->__size);
                        break;
                    }
                }
                else
                {
                    last = current;
                }
            }
            this->invalidateCentroid();
            return removePoint;
        }
        return removePoint;
    }

    // Overloaded operators

    // IO
    std::ostream &operator<<(std::ostream &stream, const Cluster & cluster)
    {
        LNodePtr currentNode = cluster.__points;//Current Node
        int clusterID = cluster.__id;

        for(currentNode; currentNode!= nullptr; currentNode = currentNode->next)
        {
            stream << *currentNode->p;
            stream << Cluster::POINT_CLUSTER_ID_DELIM << clusterID - 1 << std::endl;
        }
        return stream;
    }

    std::istream &operator>>(std::istream &stream, Cluster &cluster)
    {
        std::string line;
        getline(stream,line);
        int pSize = std::count(line.begin(),line.end(),',') + 1;
        std::stringstream ss(line);
        PointPtr newPoint = new Clustering::Point(pSize);
        ss >> *newPoint;
        cluster.add(newPoint);

        while (getline(stream, line))
        {
            std::stringstream lineStream(line);
            PointPtr newPoint = new Clustering::Point(pSize);

            lineStream >> *newPoint;

            cluster.add(newPoint);
        }
        return stream;
    }
    // Set-preserving operators (do not duplicate points in the space)
    // - Friends
    bool operator==(const Cluster &lhs, const Cluster &rhs)
    {
        LNodePtr currentR = rhs.__points;
        LNodePtr currentL = lhs.__points;

        if(lhs.__size == rhs.__size)
        {
            for (currentL; currentL != nullptr; currentL = currentL->next)
            {
                if(currentL->p != currentR->p)
                    return false;
                else
                    currentR = currentR->next;
            }
            return true;
        }
        return false;
    }

    // - Members
    const PointPtr & Cluster::operator[](unsigned int index) const
    {
        LNodePtr current = this->__points;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->p;
    }

    Cluster & Cluster::operator+=(const Cluster &rhs){
        if (this->__size == 0){
            for (LNodePtr rhsNodeCursor = rhs.__points; rhsNodeCursor != nullptr; rhsNodeCursor = rhsNodeCursor->next) {
                this->add(rhsNodeCursor->p);
            }
        } else {
            // iterate through all the nodes within the RHS cluster
            for (LNodePtr rhsNodeCursor = rhs.__points; rhsNodeCursor != nullptr; rhsNodeCursor = rhsNodeCursor->next){
                bool addPoint = true;
                for (LNodePtr thisNodeCursor = this->__points; thisNodeCursor != nullptr; thisNodeCursor = thisNodeCursor->next){
                    if (thisNodeCursor->p == rhsNodeCursor->p){
                        addPoint = false;
                    }
                }
                if (addPoint){
                    this->add(rhsNodeCursor->p);
                }
            }
        }
        return *this;
    }/*
    Cluster &Cluster::operator+=(const Cluster &rhs) // union
    {
        if(rhs.__size > 0)
        {
            LNodePtr current = rhs.__points;
            for(int i = 0; i < rhs.__size; i++)
            {
                add(current->p);//Just let add figure out where to put it, including duplicates since it was not specified if they needed to be deleted.
                current = current->next;
            }
        }
        else
        {
            *this = rhs;
        }
        return *this;
    }*/

    Cluster &Cluster::operator-=(const Cluster &rhs) // (asymmetric) difference
    {
        if(rhs.__size > 0)
        {
            LNodePtr current = rhs.__points;
            for(int i = 0; i < rhs.__size; i++)
            {
                remove(current->p);//Just let add figure out where to put it, including duplicates since it was not specified if they needed to be deleted.
                current = current->next;
            }
        }
        return *this;
    }

    Cluster &Cluster::operator+=(const Point &point) // add point
    {
        PointPtr pointer =  new Point(point);
        this->add(pointer);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &point) // remove point
    {
        LNodePtr current = this->__points;
        for (current; current != nullptr; current = current->next)
        {
            if (*current->p == point)
            {
                this->remove(current->p);
                break;
            }
        }
        return *this;
    }


    // Set-destructive operators (duplicate points in the space)
    // - Friends
    const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
    {
        Cluster result = lhs;
        result += rhs;
        return result;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
    {
        Cluster result = lhs;
        result -= rhs;
        return result;
    }


    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster result = lhs;
        result.add(rhs);
        return result;
    }

    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs)
    {
        Cluster result = lhs;
        result.remove(rhs);
        return result;
    }
}

