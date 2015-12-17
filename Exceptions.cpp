#include "Exceptions.h"

using namespace std;

namespace Clustering
{
    //---------------------------------------------DimsensionalityMismatchEx-----------------------------------------/
    DimensionalityMismatchEx::DimensionalityMismatchEx(string name) {
        this->resetError();
        this->name = name;
        this->errMessage = "Dimensionality Mismatch Error";
    }

    ostream &operator<<(ostream & os, DimensionalityMismatchEx & dimErr) {
        os.width(4);
        os << dimErr.getLine() << ": ";
        os.width(65);
        os.setf(ios::left, ios::adjustfield);
        os << dimErr.getName() << "  ";
        os.setf(ios::right, ios::adjustfield);
        os << dimErr.getErr() << "\n";
        os.flush();
    }
}
}