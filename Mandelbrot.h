//
// Created by Anass on 2024-05-18.
//

#ifndef FRACTALS_MANDELBROT_H
#define FRACTALS_MANDELBROT_H
namespace abbouspace {

    class Mandelbrot {
    public:
        static const int MAX_ITERATIONS = 1000;

    public:
        Mandelbrot();

        virtual ~Mandelbrot();

        static int getIterations(double x, double y);
    };

}
#endif //FRACTALS_MANDELBROT_H
