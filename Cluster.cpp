#include "Cluster.h"

namespace Clustering 
{
    // The big three: cpy ctor, overloaded operator=, dtor
    Cluster::Cluster(const Cluster & copy)
    {
        size = copy.size;
        points = copy.points;
    }

    Cluster &Cluster::operator=(const Cluster & copy)
    {
        if (this != &copy)
        {
            size = copy.size;
            points = copy.points;
        }
        return *this;
    }

    Cluster::~Cluster()
    {

    }

    // Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const PointPtr &newPoint)
    {
        LNodePtr node = new LNode();

        if(points == nullptr)
        {
            points = node;
            points->p = newPoint;
            node->next = nullptr;
        }
        else
        {
            LNodePtr current = points;
            PointPtr currentPoint = points->p;

            for(int i = 0; i < size; i ++)
            {
                if(newPoint > currentPoint || newPoint == currentPoint)//We found where to put it
                {
                    LNodePtr temp = current; //Save point to move.

                    current = node; //Assign blank node, add point, set next.
                    current->p = newPoint;
                    current->next = temp;
                    break;
                }
                else if(current->next != nullptr) //move to the next val
                {
                    current = current->next;
                    currentPoint = current->p;
                }
                else //List ended, add it to the end.
                {
                    current->next = node;
                    current->next->p = newPoint;
                    current->next->next = nullptr;
                }
            }
        }
        size++;
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
                std::cout << "Node Not Found in List!" << std::endl;//Alert user node is not in list.
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
    }//nope
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
                add()
            }
        }
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

