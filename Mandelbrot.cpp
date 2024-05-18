//
// Created by Anass on 2024-05-18.
//

#include <complex>
#include "Mandelbrot.h"
using namespace std;

namespace abbouspace {

    Mandelbrot::Mandelbrot() {}




     int Mandelbrot::getIterations(double x, double y) {
        complex<double> z=0;
        complex<double> c(x, y);

        int iterations=0;
        while(iterations < Mandelbrot::MAX_ITERATIONS){
            z= z*z*z +c;

            if(abs(z)>2){
                break;
            }
            iterations++;

        }

        return iterations ;
    }




Mandelbrot::~Mandelbrot() {}

}