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
            // z= (((2.0 / 3.0) * pow(z, 3.0) - 2.0 * z - 1.0) / pow((z + 1.0), 2.0)) + c + 1.0;
                z=z*z+c;
            //*****
            if(abs(z)>2){
                break;
            }
            iterations++;

        }

        return iterations ;
    }




Mandelbrot::~Mandelbrot() {}

}