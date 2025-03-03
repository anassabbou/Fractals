#ifndef FRACTALS_SIERPINSKI_H
#define FRACTALS_SIERPINSKI_H

namespace abbouspace {

    class Sierpinski {
    public:
        static const int MAX_ITERATIONS = 1000;

        Sierpinski();
        int getIterations(double x, double y);
        ~Sierpinski();
    };
}

#endif // FRACTALS_SIERPINSKI_H
