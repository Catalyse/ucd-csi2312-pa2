#include "Exceptions.h"

using namespace std;

namespace Clustering
{
    //---------------------------------------------DimsensionalityMismatchEx-----------------------------------------/
    DimensionalityMismatchEx::DimensionalityMismatchEx() {}

    DimensionalityMismatchEx::DimensionalityMismatchEx(string error)
    {
        this->message = error;
    }

    ostream &operator<<(ostream & stream, DimensionalityMismatchEx & error)
    {
        stream << error.getName() << " :: " << error.getError() << "\n";
    }

    //--------------------------------------------OutOfBoundsEx-----------------------------------------------------/
    OutOfBoundsEx::OutOfBoundsEx() {}
    OutOfBoundsEx::OutOfBoundsEx(string error)
    {
        this->message = error;
    }

    ostream &operator<<(ostream & stream, OutOfBoundsEx & error)
    {
        stream << error.getName() << " :: " << error.getError() << "\n";
    }

    //------------------------------------------RemoveFromEmptyEx---------------------------------------------------/
    RemoveFromEmptyEx::RemoveFromEmptyEx()
    {
        this->message = "Object is empty, cannot remove from it.";
    }

    RemoveFromEmptyEx::RemoveFromEmptyEx(string error)
    {
        this->message = error;
    }

    ostream &operator<<(ostream & stream, RemoveFromEmptyEx & error)
    {
        stream << error.getName() << " :: " << error.getError() << "\n";
    }
}
