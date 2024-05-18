#include <iostream>
#include "Bitmap/Bitmap.h"
#include "Mandelbrot/Mandelbrot.h"
#include <cstdint>
#include <memory>
#include <math.h>

using namespace abbouspace;
using namespace std;
int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    Bitmap bitmap(WIDTH, HEIGHT);

    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}); //Histogram: store number of iterations got by pixel ,  < MaxIteration using smart pointer
    unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]{0}); // Fractal:  write information of pixels: pixels numbering from left -> right, working row by row across the screen

    for(int y=0; y<HEIGHT; y++){
        for(int x=0; x<WIDTH; x++){
            // ******** control
            double xMoving=20, yMoving=10;
            double yZoom=HEIGHT - 200, xZoom=HEIGHT -100;
            // **********
            double xFractal =((x - WIDTH/2) - xMoving) * 2.0/xZoom;
            double yFractal=(y - HEIGHT/2 + yMoving) * 2.0/(yZoom);
            int  iterations= Mandelbrot::getIterations(xFractal,yFractal);
            fractal[y * WIDTH + x]= iterations;

            if(iterations != Mandelbrot::MAX_ITERATIONS){
                histogram[iterations]++;
            }
        }
    }

    int total=0;
    for(int i=0; i<Mandelbrot::MAX_ITERATIONS; i++){
        total += histogram[i];
    }


    for(int y = 0; y < HEIGHT; y++){
        for(int x=0; x < WIDTH; x++){
            uint8_t  red=0, green=0, blue=0;
            int iterations = fractal[y * WIDTH + x];
            if(iterations != Mandelbrot::MAX_ITERATIONS) {

                double hue = 0.0;

                for (int i = 0; i <= iterations; i++) {
                    hue += ((double) histogram[i]) / total;
                }

                green = pow(0,hue);
                red = pow(153,hue);
                blue= pow(153,hue);
                bitmap.setPixel(x, y, red, green, blue);
            }
        }
    }

    bitmap.write("../generated_images/test1.bmp");
    cout<< "Finished." << endl;

    return 0;
}
