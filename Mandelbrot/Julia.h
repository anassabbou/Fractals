#ifndef FRACTALS_JULIA_H
#define FRACTALS_JULIA_H

namespace abbouspace {

    class Julia {
    public:
        static const int MAX_ITERATIONS = 1000;

        Julia();
        int getIterations(double x, double y);
        ~Julia();
    };
}

#endif // FRACTALS_JULIA_H
