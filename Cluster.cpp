#include "Cluster.h"
#include <sstream>
#include <algorithm> //For counting

namespace Clustering 
{
    // The big three: cpy ctor, overloaded operator=, dtor
    Cluster::Cluster(const Cluster & copy) : __centroid(copy.getDimensionality())
    {
        if (this == &copy)
        {
            // dont copy self
        }
        else
        {
            this->__size = 0;
            this->__dimensionality = copy.__dimensionality;
            this->__points = nullptr;
            this->__release_points = copy.__release_points;
            this->__greedy = copy.__greedy;
            this->__id = copy.getId();
            for (LNodePtr current = copy.__points; current != nullptr; current = current->next)
            {
                this->add(current->p);
            }
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

    void Cluster::computeCentroid()
    {
        PointPtr centroid = new Point(this->__dimensionality);
        int count = 0;
        int tLoops = 0;
        for (LNodePtr current = this->__points; current != nullptr; current = current->next)
        {
            *centroid += *current->p;
        }
        *centroid /= this->getSize();
        this->setCentroid(*centroid);
    }

    // Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const PointPtr &newPoint)
    {
        if(pointDims != 0 && newPoint->getDims() != pointDims)
        {
            //std::cout << "Invalid Point: Cannot add different sized points to a cluster!" << std::endl;
        }
        else
        {
            LNodePtr node = new LNode();

            if (__points == nullptr)
            {
                __points = node;
                __points->p = newPoint;
                node->next = nullptr;
                pointDims = newPoint->getDims();//Set our Clusters point size type when the first element is added.
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
            LNodePtr current = __points;
            LNodePtr last;
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
            //this->invalidateCentroid();
            return removePoint;
        }
        return removePoint;
    }

    // Overloaded operators

    // IO
    std::ostream &operator<<(std::ostream &stream, const Cluster & cluster)
    {
        if (cluster.__size != 0)
        {
            LNodePtr currentNode = cluster.__points;//Current Node
            PointPtr point = cluster.__points->p;//Current Node point

            std::cout << *point;

            while(currentNode->next != nullptr)
            {
                currentNode = currentNode->next;
                point = currentNode->p;
                std::cout << *point;
            }
        }
        else
        {
            std::cout << "Cluster is empty" << std::endl;
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
            while(currentL != nullptr)
            {
                if(currentL->p != currentR->p)
                    return false;
                currentL = currentL->next;
                currentR = currentR->next;
            }
            return true;
        }
        return false;
    }

    // - Members
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
        return *this;
    }

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
    }

    Cluster &Cluster::operator-=(const Point &point) // remove point
    {
        PointPtr pointer = new Point(point);
        this->remove(pointer);
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

