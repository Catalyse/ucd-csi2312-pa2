#include "Cluster.h"
#include <sstream>
#include <algorithm> //For counting

namespace Clustering 
{
    // The big three: cpy ctor, overloaded operator=, dtor
    Cluster::Cluster(const Cluster & copy)
    {
        size = copy.size;
        points = copy.points;
        pointDims = copy.pointDims;
    }

    Cluster &Cluster::operator=(const Cluster & copy)
    {
        if (this != &copy)
        {
            size = copy.size;
            points = copy.points;
            pointDims = copy.pointDims;
        }
        return *this;
    }

    Cluster::~Cluster()
    {
        if (points != nullptr)
        {
            LNodePtr current = points;
            LNodePtr next = current->next;

            while (current != nullptr)
            {
                delete current->p;
                delete current;
                current = next;
                next = next->next;
                if (next == nullptr)
                {
                    delete current->p;
                    delete current;
                    break;
                }
            }
            std::cout << "Cluster Deleted" << std::endl;
        }
        else
            std::cout << "Empty Cluster Deleted" << std::endl;
    }

    void Cluster::setCentroid(const Point &setPoint)
    {
        if(setPoint.getDims() == pointDims)
        {
            PointPtr newCenter = new Point(setPoint);
            centroid = newCenter;
        }
        else
            std::cout << "Invalid Set Point!  Point to set centroid MUST have the same dimensions as the cluster." << std::endl << "Current Cluster Point Dims(Cluster type) is: " << pointDims << std::endl;
    }

    const Point Cluster::getCentroid()
    {
        Point returnPoint = *centroid;
        return returnPoint;
    }

    void Cluster::computeCentroid()
    {
        centroid = new Point(pointDims);//Reset the centroid

        LNodePtr current = points;

        for (int i = 0; i < pointDims; i++)
        {
            int j = 0;
            double dimAverage = 0.0;//Make a var to store average
            while(current != nullptr)
            {
                dimAverage += current->p->getValue(j);
                current = current->next;
                j++;
            }
            dimAverage = dimAverage / j;

            centroid->setValue(i, dimAverage);

            current = points;
        }
    }

    // Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const PointPtr &newPoint)
    {
        if(pointDims != 0 && newPoint->getDims() != pointDims)
        {
            std::cout << "Invalid Point: Cannot add different sized points to a cluster!" << std::endl;
        }
        else
        {
            LNodePtr node = new LNode();

            if (points == nullptr)
            {
                points = node;
                points->p = newPoint;
                node->next = nullptr;
                pointDims = newPoint->getDims();//Set our Clusters point size type when the first element is added.
            }
            else
            {
                LNodePtr current = points;
                PointPtr currentPoint = points->p;

                if (*newPoint > *currentPoint || *newPoint == *currentPoint)
                {
                    points = node;
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
            size++;
        }
    }

    const PointPtr &Cluster::remove(const PointPtr & removePoint)
    {
        if(points != nullptr)
        {
            LNodePtr current = points;
            LNodePtr last;
            while(current != nullptr)
            {
                if(current->p == removePoint)
                    break;
                else
                {
                    last = current;
                    current = current->next;
                }
            }
            if(current == nullptr)//If end of list is reached
            {
                std::cout << "Node Not Found in List!" << std::endl;//Alert user node is not in list.
                return removePoint;
            }
            else if(points == current)//remove head
                points = points->next;
            else
                last->next = current->next;
            delete current;
            size--;
        }
        return removePoint;
    }

    // Overloaded operators

    // IO
    std::ostream &operator<<(std::ostream &stream, const Cluster & cluster)
    {
        if (cluster.size != 0)
        {
            LNodePtr currentNode = cluster.points;//Current Node
            PointPtr point = cluster.points->p;//Current Node point

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
        LNodePtr currentR = rhs.points;
        LNodePtr currentL = lhs.points;

        if(lhs.size == rhs.size)
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
        if(rhs.size > 0)
        {
            LNodePtr current = rhs.points;
            for(int i = 0; i < rhs.size; i++)
            {
                add(current->p);//Just let add figure out where to put it, including duplicates since it was not specified if they needed to be deleted.
                current = current->next;
            }
        }
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rhs) // (asymmetric) difference
    {
        if(rhs.size > 0)
        {
            LNodePtr current = rhs.points;
            for(int i = 0; i < rhs.size; i++)
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

