#include <complex>
#include "Julia.h"

using namespace std;

namespace abbouspace {

    Julia::Julia() {}

    int Julia::getIterations(double x, double y) {
        complex<double> z(x, y);
        complex<double> c(-0.7, 0.27015); // Example constant for Julia set

        int iterations = 0;
        while (iterations < Julia::MAX_ITERATIONS) {
            z = z * z + c;
            if (abs(z) > 2) {
                break;
            }
            iterations++;
        }

        return iterations;
    }

    Julia::~Julia() {}
}
