// ClusteringTests.cpp
//
// Created by Ivo Georgiev on 10/29/15.
//

#include <iostream>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <limits>

#include "ClusteringTests.h"
#include "Point.h"
#include "Cluster.h"

using namespace Clustering;
using namespace Testing;

#define DESC(x) desc(x, __LINE__)  // ugly hack, but saves some time




// - - - - - - - - - - helper functions - - - - - - - - - -
const Point point_in_and_out(const Point p) { return Point(p); }



// - - - - - - - - - - T E S T S - - - - - - - - - -

// - - - - - - - - - - P O I N T - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor
void test_point_smoketest(ErrorContext &ec) {
    bool pass;

    ec.DESC("--- Test - Point - Smoketest ---");

    ec.DESC("constructor, dimensionality, destructor");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        // Construct a Point
        // At the end of the block, destructor will be called
        Point p(10);

        pass = (p.getDims() == 10);
        if (!pass) break;
    }
    ec.result(pass);


    ec.DESC("constructor, large size");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        // Construct a Point
        // At the end of the block, destructor will be called
        Point p(1000000);

        pass = (p.getDims() == 1000000);
        if (!pass) break;
    }
    ec.result(pass);


    ec.DESC("copy constructor");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        // Construct a Point
        // At the end of the block, destructor will be called
        Point p1(10);
        Point p2(p1);

        pass = (p1.getDims() == 10 && p2.getDims() == 10);
        if (!pass) break;
    }
    ec.result(pass);
}

// setValue, getValue, operator[]
void test_point_getsetelem(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Get/set element ---");

    for (int run = 0; run < numRuns; run ++)
    {
        ec.DESC("values default to zero");

        {
            Point p(50);

            // Check zeros
            pass = true;
            for (int i = 0; i < 50; i ++) {
                pass = pass &&
                        (p.getValue(i + 1) == 0.0) &&
                        (p[i + 1] == 0.0);
            }
            ec.result(pass);
        }

        ec.DESC("setValue, getValue (1-indexed)");

        {
            Point p(20);

            // Set values
            for (int i = 0; i < 20; i ++)
                p.setValue(i + 1, 13.43 * i * i + 4.567 * i + 1.234567);

            // Check values
            pass = true;
            for (int i = 0; i < 20; i++)
                pass = pass &&
                        (p.getValue(i + 1) == (13.43 * i * i + 4.567 * i + 1.234567)) &&
                        (p.getValue(i + 1) == (13.43 * i * i + 4.567 * i + 1.234567));
            ec.result(pass);
        }

        ec.DESC("operator[] (1-indexed)");

        {
            Point p(5);

            // Set values
            for (int i = 0; i < 5; i ++)
                p[i + 1] = 1000000.43 * i * i + 400000.567 * i + 10000.234567;

            // Check values
            pass = true;
            for (int i = 0; i < 5; i ++)
                pass = pass &&
                       (p.getValue(i + 1) == (1000000.43 * i * i + 400000.567 * i + 10000.234567)) &&
                       (p[i + 1] == (1000000.43 * i * i + 400000.567 * i + 10000.234567));
            ec.result(pass);
        }
    }
}

// Copy constructor
void test_point_copying(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Copy ---");

    for (int run = 0; run < numRuns; run ++) {

        ec.DESC("simple copy");

        {
            Point p1(50);

            for (int i = 0; i < 50; i ++)
                p1[i + 1] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(p1);

            pass = true;
            for (int i = 0; i < 50; i ++)
                pass = pass && (p1[i + 1] == p2[i + 1]);
            ec.result(pass);
        }

        ec.DESC("pass and return by value");

        {
            Point p1(50);

            for (int i = 0; i < 50; i ++)
                p1[i + 1] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2 = point_in_and_out(p1);

            pass = true;
            for (int i = 0; i < 50; i ++)
                pass = pass && (p1[i + 1] == p2[i + 1]);
            ec.result(pass);
        }
    }
}

// operator=
void test_point_assignment(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Assign ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("simple assignment");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2 = p1;

            pass = true;
            for (int i = 0; i < 50; i++)
                pass = pass && (p1[i + 1] == p2[i + 1]);
            ec.result(pass);
        }

        ec.DESC("chained assignment");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(50), p3(50), p4(50), p5(50);

            p2 = p3 = p4 = p5 = p1;

            pass = true;
            for (int i = 0; i < 50; i++)
                pass = pass && (p1[i + 1] == p2[i + 1]);
            ec.result(pass);
        }
    }
}

// operator==, operator!=
void test_point_equality(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Equal ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("compare equal");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(p1);

            pass = (p2 == p1);
            ec.result(pass);
        }


        ec.DESC("ensure operator== is not a dummy");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(p1);
            p2[1] = p2[1] + 1.0;

            pass = !(p2 == p1);
            ec.result(pass);
        }

        ec.DESC("compare not equal");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 44.56 * i * i + 23.45 * i + 12.34;

            Point p2(p1);
            p1[50] = p1[50] + 100.0;

            pass = (p2 != p1);
            ec.result(pass);
        }
    }
}

// operator<, operator<=, operator>, operator>=
// (pseudo-lexicographic comparison)
void test_point_comparison(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Compare ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("compare pseudo-lexicographic order");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i + 1] = i;
                p2[i + 1] = i + 1.0;
                p3[i + 1] = i + 2.0;
            }

            pass = (p1 < p2) &&
                   (p2 < p3) &&
                   (p1 < p3);
            ec.result(pass);
        }

        ec.DESC("less than, one different value, leading");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i + 1] = p2[i + 1] = p3[i + 1] = i;
            }
            p2[1] = p1[1] + std::numeric_limits<double>::epsilon();
            p3[1] = p2[1] + std::numeric_limits<double>::epsilon();

            pass = (p1 < p2) &&
                   (p2 < p3) &&
                   (p1 < p3);
            ec.result(pass);
        }

        ec.DESC("less than, one different value, middle");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i + 1] = p2[i + 1] = p3[i + 1] = i;
            }
            p2[30] = p1[30] + 0.00000001;
            p3[30] = p2[30] + 0.00000001;

            pass = (p1 < p2) &&
                   (p2 < p3) &&
                   (p1 < p3);
            ec.result(pass);
        }

        ec.DESC("less than, one different value, trailing");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i + 1] = p2[i + 1] = p3[i + 1] = i;
            }
            p2[50] = p1[50] + 0.00000001;
            p3[50] = p2[50] + 0.00000001;

            pass = (p1 < p2) &&
                   (p2 < p3) &&
                   (p1 < p3);
            ec.result(pass);
        }

        ec.DESC("less than or equal, equal values");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i + 1] = p2[i + 1] = p3[i + 1] = i;
            }

            pass = (p1 <= p2) &&
                   (p2 <= p3) &&
                   (p1 <= p3);
            ec.result(pass);
        }

        ec.DESC("less than or equal, one different value, trailing");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i + 1] = p2[i + 1] = p3[i + 1] = i;
            }
            p2[50] = p1[50] + 0.00000001;
            p3[50] = p2[50] + 0.00000001;

            pass = (p1 <= p2) &&
                   (p2 <= p3) &&
                   (p1 <= p3);
            ec.result(pass);
        }

        ec.DESC("more than or equal, equal values");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i + 1] = p2[i + 1] = p3[i + 1] = i;
            }

            pass = (p1 >= p2) &&
                   (p2 >= p3) &&
                   (p1 >= p3);
            ec.result(pass);
        }

        ec.DESC("more than or equal, one different value, middle");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i + 1] = p2[i + 1] = p3[i + 1] = i;
            }

            p2[30] = p3[30] + 0.00000001;
            p1[30] = p2[30] + 0.00000001;

            pass = (p1 >= p2) &&
                   (p2 >= p3) &&
                   (p1 >= p3);
            ec.result(pass);
        }

        ec.DESC("more than, one different value, middle");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i ++) {
                p1[i + 1] = p2[i + 1] = p3[i + 1] = i;
            }

            p2[30] = p3[30] + 0.00000001;
            p1[30] = p2[30] + 0.00000001;

            pass = (p1 > p2) &&
                   (p2 > p3) &&
                   (p1 > p3);
            ec.result(pass);
        }
    }
}

// operator+=, operator-=, operator*=, operator/=
void test_point_CAO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Compound arithmetic ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("plus equals (two points)");

        {
            Point p1(50), p2(50);

            for (int i = 0; i < 50; i++) {
                p1[i + 1] = i;
                p2[i + 1] = i + 1;
            }

            Point p3(50);
            p3 += p1 += p2;
            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p3[i + 1] == 2 * i + 1);
            }
            ec.result(pass);
        }

        ec.DESC("minus equals (two points)");

        {
            Point p1(50), p2(50), p3(50);

            for (int i = 0; i < 50; i++) {
                p1[i + 1] = i;
                p2[i + 1] = i + 1;
                p3[i + 1] = 3 * i + 1;
            }

            p3 -= p2 -= p1;
            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p3[i + 1] == 3 * i);
            }
            ec.result(pass);
        }

        ec.DESC("times equals (point and double)");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++) {
                p1[i + 1] = i;
            }

            p1 *= 3.14;

            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p1[i + 1] == 3.14 * i);
            }
            ec.result(pass);
        }

        ec.DESC("divide equals (point and double)");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++) {
                p1[i + 1] = 100.0 * i;
            }

            p1 /= 3.14;

            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p1[i + 1] == 100.0 * i / 3.14);
            }
            ec.result(pass);
        }
    }
}

// operator+, operator-, operator*, operator/
void test_point_SAO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Simple arithmetic ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("plus (two points)");

        {
            Point p1(50), p2(50);

            for (int i = 0; i < 50; i++) {
                p1[i + 1] = i;
                p2[i + 1] = i + 1;
            }

            Point p3 = p1 + p2;
            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p3[i + 1] == 2 * i + 1);
            }
            ec.result(pass);
        }

        ec.DESC("minus (two points)");

        {
            Point p1(50), p2(50);

            for (int i = 0; i < 50; i++) {
                p1[i + 1] = i + 1;
                p2[i + 1] = 2 * i - 1;
            }

            Point p3 = p2 - p1;
            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p3[i + 1] == i - 2);
            }
            ec.result(pass);
        }

        ec.DESC("times (point and double)");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++) {
                p1[i + 1] = i;
            }

            Point p2 = p1 * 3.14;

            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p2[i + 1] == 3.14 * i);
            }
            ec.result(pass);
        }

        ec.DESC("divide (point and double)");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++) {
                p1[i + 1] = 100.0 * i;
            }

            Point p2 = p1 / 3.14;

            pass = true;
            for (int i = 0; i < 50; i++) {
                pass = pass && (p2[i + 1] == 100.0 * i / 3.14);
            }
            ec.result(pass);
        }
    }
}

// distanceTo
void test_point_distance(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Distance ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("same point");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 2.4 * i * i + 1.3 * i + 6.7;

            Point p2(p1);

            pass = (p1.distanceTo(p2) == 0);
            ec.result(pass);
        }

        ec.DESC("5 units away");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = i;

            Point p2(p1);
            p2[1] += 5;

            pass = (p1.distanceTo(p2) == 5);
            if (!pass) std::cout << p1.distanceTo(p2) << " ";
            ec.result(pass);
        }

        // Integer sequence A180442

        ec.DESC("distance 1612 from origin");

        {
            Point p1(169); // 198 - 29

            unsigned int start = 30;
            for (int i = 0; i < 169; i++) {
                p1[i + 1] = start;
                start++;
            }

            Point origin(169); // relies on initialization to zeros

            pass = (p1.distanceTo(origin) == 1612);
            if (!pass) std::cout << p1.distanceTo(origin) << " ";
            ec.result(pass);
        }
    }
}

// operator>>, operator<< (incl. exceptions)
void test_point_IO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Point - Stream IO ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("stream between two points");

        {
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 6.12 * i * i + 5.17 * i + 4.19;

            Point p2(50);
            std::stringstream iostr;
            iostr << std::setprecision(20) << p1; // Avoid truncation
            iostr >> p2;

            pass = true;
            for (int i = 0; i < 50; i++)
                pass = pass && (p2[i + 1] == p1[i + 1]);
            if (!pass) {
                std::cout << p1 << std::endl;
                std::cout << p2 << std::endl;
            }
            ec.result(pass);

        }
    }
}


// - - - - - - - - - - C L U S T E R - - - - - - - - - -

// Smoketest: constructor, copy constructor, destructor
void test_cluster_smoketest(ErrorContext &ec) {
    bool pass;

    ec.DESC("--- Test - Cluster - Smoketest ---");

    ec.DESC("constructor, destructor");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        Cluster c;
    }
    ec.result(pass);


    ec.DESC("size getter - implement if you haven't");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        // Construct a Point
        // At the end of the block, destructor will be called
        Cluster c;

        pass = (c.getSize() == 0);
        if (!pass) break;
    }
    ec.result(pass);


    ec.DESC("copy constructor");
    pass = true;
    for (int i = 0; i < 10; i ++) {

        Cluster c1, c2(c1);

        pass = (c1 == c2);
        if (!pass) break;
    }
    ec.result(pass);
}

// add, remove
void test_cluster_addremove(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Add/remove points ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("add and check with size getter");

        {
            Cluster c1;
            c1.add(new Point(50));
            c1.add(new Point(50));
            c1.add(new Point(50));

            pass = (c1.getSize() == 3);

            ec.result(pass);
        } // by default, points will get released here


        ec.DESC("add, remove, and check with size getter");

        {
            // Note that the PA2 Cluster works with pointers
            // To check equality, two clusters should have
            // the same pointers added to them
            Point   *p1 = new Point(10),
                    *p2 = new Point(10),
                    *p3 = new Point(10);
            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            c1.remove(p1); c1.remove(p2); c1.remove(p3);

            pass = (c1.getSize() == 0);

            ec.result(pass);
        } // by default, points will get released here

        ec.DESC("add, check with cluster equality, remove");

        {
            // Note that the PA2 Cluster works with pointers
            // To check equality, two clusters should have
            // the same pointers added to them
            Point   *p1 = new Point(10),
                    *p2 = new Point(10),
                    *p3 = new Point(10);

            Cluster c1, c2;
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p1); c2.add(p2); c2.add(p3);

            pass = (c1 == c2);
            // don't forget to remove the points from one
            // of the clusters to avoid the "double delete"
            c2.remove(p1); c2.remove(p2); c2.remove(p3);

            ec.result(pass);
        }

        ec.DESC("check point after add and remove");

        {
            Point   *p1 = new Point(10);

            for (int i = 0; i < 10; i++)
                (*p1)[i + 1] = 5.4 * i * i + 3.4 * i + 1.6;

            Cluster c1;
            c1.add(p1);
            Point *p2 = c1.remove(p1);

            pass = (p1 == p2);

            ec.result(pass);
        }
    }
}

// Copy constructor
void test_cluster_copying(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Copy ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("simple copy");

        {
            // Note that the PA2 Cluster works with pointers
            // To check equality, two clusters should have
            // the same pointers added to them
            Point   *p1 = new Point(10),
                    *p2 = new Point(10),
                    *p3 = new Point(10);

            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2(c1);

            pass = (c1 == c2);
            // don't forget to remove the points from one
            // of the clusters to avoid the "double delete"
            c2.remove(p1); c2.remove(p2); c2.remove(p3);

            ec.result(pass);
        }

        ec.DESC("chained copy");

        {
            Point   *p1 = new Point(10),
                    *p2 = new Point(10),
                    *p3 = new Point(10);

            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2(c1), c3(c2), c4(c3);

            pass = (c1 == c4);

            // avoid double delete
            c1.remove(p1); c1.remove(p2); c1.remove(p3);
            c2.remove(p1); c2.remove(p2); c2.remove(p3);
            c3.remove(p1); c3.remove(p2); c3.remove(p3);

            ec.result(pass);
        }
    }
}

// operator=
void test_cluster_assignment(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Assign ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("simple assignment");

        {
            // Note that the PA2 Cluster works with pointers
            // To check equality, two clusters should have
            // the same pointers added to them
            Point   *p1 = new Point(10),
                    *p2 = new Point(10),
                    *p3 = new Point(10);

            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2 = c1;

            pass = (c1 == c2);
            // don't forget to remove the points from one
            // of the clusters to avoid the "double delete"
            c2.remove(p1); c2.remove(p2); c2.remove(p3);

            ec.result(pass);
        }


        ec.DESC("assignment causing deletion");

        {
            // Note that the PA2 Cluster works with pointers
            // To check equality, two clusters should have
            // the same pointers added to them
            Point   *p1 = new Point(10),
                    *p2 = new Point(10),
                    *p3 = new Point(10);

            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2;
            // add some other points
            c2.add(new Point(10));
            c2.add(new Point(10));
            c2.add(new Point(10));

            c2 = c1;

            pass = (c1 == c2);
            // don't forget to remove the points from one
            // of the clusters to avoid the "double delete"
            c2.remove(p1); c2.remove(p2); c2.remove(p3);

            ec.result(pass);
        }

        ec.DESC("chained assignment");

        {
            Point   *p1 = new Point(10),
                    *p2 = new Point(10),
                    *p3 = new Point(10);

            Cluster c1;
            c1.add(p1); c1.add(p2); c1.add(p3);
            Cluster c2 = c1;
            Cluster c3 = c2;
            Cluster c4 = c3;

            pass = (c1 == c4);

            // avoid double delete
            c1.remove(p1); c1.remove(p2); c1.remove(p3);
            c2.remove(p1); c2.remove(p2); c2.remove(p3);
            c3.remove(p1); c3.remove(p2); c3.remove(p3);

            ec.result(pass);
        }
    }
}

// operator==
void test_cluster_equality(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Equal ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("check operator== is not a dummy");

        {
            // The requirements don't provide for many other methods that
            // can be used for testing, so operator== is checked first
            Cluster c1, c2;
            c1.add(new Point(100));

            pass = !(c1 == c2);

            ec.result(pass);
        }
    }
}

// operator+=, operator-=, different rhs
void test_cluster_CAO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Compound arithmetic ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("plus equals (Cluster and Point) check with non-equality");

        {
            Cluster c1, c2;
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 6.75 * i * i + 5.45 * i + 1.15;

            c1 += p1;

            pass = !(c1 == c2);

            ec.result(pass);
        }

        ec.DESC("plus equals (Cluster and Point) check with size getter");

        {
            Cluster c1;
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 6.75 * i * i + 5.45 * i + 1.15;

            c1 += p1;

            pass = (c1.getSize() == 1);

            ec.result(pass);
        }

        ec.DESC("minus equals (Cluster and Point) check with non-equality");

        {
            Cluster c1, c2;
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 6.75 * i * i + 5.45 * i + 1.15;

            c1 += p1;
            pass = !(c1 == c2);

            c1 -= p1;
            pass = (c1 == c2);

            ec.result(pass);
        }

        ec.DESC("minus equals (Cluster and Point) check with size getter");

        {
            Cluster c1;
            Point p1(50);

            for (int i = 0; i < 50; i++)
                p1[i + 1] = 6.75 * i * i + 5.45 * i + 1.15;

            c1 += p1;
            pass = (c1.getSize() == 1);

            c1 -= p1;
            pass = (c1.getSize() == 0);

            ec.result(pass);
        }

        ec.DESC("plus equals (Cluster union) no common points");

        {
            Cluster c1, c2, c3;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50),
                    *p5 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p4); c2.add(p5);

            // create a union to compare to
            c3.add(p1); c3.add(p2); c3.add(p3);
            c3.add(p4); c3.add(p5);

            c1 += c2;

            pass = (c1 == c3);

            // clean up - leave the points only in c1
            c2.remove(p4); c2.remove(p5);

            c3.remove(p1); c3.remove(p2); c3.remove(p3);
            c3.remove(p4); c3.remove(p5);

            // NOTE: if you get a segfault here, this is most
            // probably the double delete

            ec.result(pass);
        }

        ec.DESC("plus equals (Cluster union) one common point");

        {
            Cluster c1, c2, c3;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50),
                    *p5 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p3); c2.add(p4); c2.add(p5);

            // create a union to compare to
            c3.add(p1); c3.add(p2); c3.add(p3);
            c3.add(p4); c3.add(p5);

            c1 += c2;

            pass = (c1 == c3);

            // clean up - leave the points only in c1
            c2.remove(p3); c2.remove(p4); c2.remove(p5);

            c3.remove(p1); c3.remove(p2); c3.remove(p3);
            c3.remove(p4); c3.remove(p5);

            // NOTE: if you get a segfault here, this is most
            // probably the double delete

            ec.result(pass);
        }

        ec.DESC("plus equals (Cluster union) two equal clusters");

        {
            Cluster c1, c2;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50),
                    *p5 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3); c1.add(p4); c1.add(p5);
            c2.add(p1); c2.add(p2); c2.add(p3); c2.add(p4); c2.add(p5);

            c1 += c2;

            pass = (c1 == c2);

            // clean up - leave the points only in c1
            c2.remove(p1); c2.remove(p2); c2.remove(p3); c2.remove(p4); c2.remove(p5);

            ec.result(pass);
        }

        ec.DESC("minus equals (asymmetric Cluster difference) no common points");

        {
            Cluster c1, c2, c3;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50),
                    *p5 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p4); c2.add(p5);

            c3 = c1;
            c1 -= c2;

            pass = (c1 == c3);

            // clean up - leave the points only in c1 and c2
            c3.remove(p1); c3.remove(p2); c3.remove(p3);

            // NOTE: if you get a segfault here, this is most
            // probably the double delete

            ec.result(pass);
        }

        ec.DESC("minus equals (asymmetric Cluster difference) one common point");

        {
            Cluster c1, c2, c3;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50),
                    *p5 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p3); c2.add(p4); c2.add(p5);

            // Prepare a difference to compare to
            c3.add(p1); c3.add(p2);
            c1 -= c2;

            pass = (c1 == c3);

            // clean up - leave the points only in c1 and c2
            c3.remove(p1); c3.remove(p2);

            // NOTE: if you get a segfault here, this is most
            // probably the double delete

            ec.result(pass);
        }

        ec.DESC("minus equals (asymmetric Cluster difference) two equal clusters");

        {
            Cluster c1, c2, c3;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50),
                    *p5 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3); c1.add(p4); c1.add(p5);
            c2.add(p1); c2.add(p2); c2.add(p3); c2.add(p4); c2.add(p5);

            c1 -= c2;

            pass = (c1 == c3); // c1 should be empty

            ec.result(pass);
        }
    }
}

// operator+, operator-, different rhs
void test_cluster_SAO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Simple arithmetic ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("plus (Cluster and Point (pointer))");

        {
            Cluster c1, c2;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3);

            c2 = c1; c2.add(p4);
            Cluster c3 = c1 + p4;

            pass = (c3 == c2);

            // clean up
            c1.remove(p1); c1.remove(p2); c1.remove(p3);
            c2.remove(p1); c2.remove(p2); c2.remove(p3); c2.remove(p4);

            ec.result(pass);

        }

        ec.DESC("minus (Cluster and Point (pointer))");

        {
            Cluster c1, c2;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3); c1.add(p4);

            c2 = c1; c2.remove(p4);
            Cluster c3 = c1 - p4;

            pass = (c3 == c2);

            // clean up
            c2.remove(p1); c2.remove(p2); c2.remove(p3);
            c3.remove(p1); c3.remove(p2); c3.remove(p3);

            ec.result(pass);
        }

        ec.DESC("plus (Cluster union)");

        {
            Cluster c1, c2;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50),
                    *p5 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p4); c2.add(p5);

            Cluster c3;
            c3.add(p1); c3.add(p2); c3.add(p3); c3.add(p4); c3.add(p5);

            Cluster c4 = c1 + c2; // !!! Returned by value, so pointers will be deallocated by temp copy

            pass = (c4 == c3);

            // clean up
            c1.remove(p1); c1.remove(p2); c1.remove(p3);
            c2.remove(p4); c2.remove(p5);
            c3.remove(p1); c3.remove(p2); c3.remove(p3); c3.remove(p4); c3.remove(p5);
            c4.remove(p1); c4.remove(p2); c4.remove(p3); c4.remove(p4); c4.remove(p5);

            ec.result(pass);
        }

        ec.DESC("minus (Cluster difference)");

        {
            Cluster c1, c2;
            Point   *p1 = new Point(50),
                    *p2 = new Point(50),
                    *p3 = new Point(50),
                    *p4 = new Point(50),
                    *p5 = new Point(50);
            c1.add(p1); c1.add(p2); c1.add(p3);
            c2.add(p3); c2.add(p4); c2.add(p5);

            Cluster c3;
            c3.add(p1); c3.add(p2);

            Cluster c4 = c1 - c2; // !!! Returned by value, so pointers will be deallocated by temp copy

            pass = (c4 == c3);

            // clean up
            c1.remove(p1); c1.remove(p2); c1.remove(p3);
            c2.remove(p3); c2.remove(p4); c2.remove(p5);
            c3.remove(p1); c3.remove(p2);
            c4.remove(p1); c4.remove(p2);

            ec.result(pass);
        }
    }
}

// operator>>, operator<<
void test_cluster_IO(ErrorContext &ec, unsigned int numRuns) {
    bool pass;

    // Run at least once!!
    assert(numRuns > 0);

    ec.DESC("--- Test - Cluster - Stream IO ---");

    for (int run = 0; run < numRuns; run++) {

        ec.DESC("read from a file");

        {
            std::ifstream csv("points.csv");
            Cluster c;
            if (csv.is_open()) {
                csv >> c;
                csv.close();
            }
            pass = (c.getSize() == 4);

            ec.result(pass);
        }

        ec.DESC("read, write, and read again");

        {
            std::ifstream csv("points.csv");
            Cluster c;
            if (csv.is_open()) {
                csv >> c;
                csv.close();
            }
            pass = (c.getSize() == 4);

            // add a point
            c.add(new Point(5));

            std::ofstream csv1("points1.csv", std::ofstream::out);

            csv1 << c;
            csv1.close();

            std::ifstream csv2("points1.csv");
            Cluster c2;
            if (csv2.is_open()) {
                csv2 >> c2;
                csv2.close();
            }
            pass = pass && (c2.getSize() == 5);

            ec.result(pass);
        }
    }
}