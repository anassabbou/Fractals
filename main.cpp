#include <iostream>
#include "Bitmap.h"
#include "Mandelbrot.h"
#include <cstdint>
#include <memory>

using namespace abbouspace;
using namespace std;
int main() {
    int const WIDTH = 800;
    int const HEIGHT = 600;

    Bitmap bitmap(WIDTH, HEIGHT);
// setting pixels
    double min = 999999;
    double max = -999999;


    //Histogram: store number of iterations,  < MaxIteration using smart pointer
    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{0});

    // scaling
    for(int y=0; y<HEIGHT; y++){
        for(int x=0; x<WIDTH; x++){
            double xFractal =(x- WIDTH/2 -200) * 2.0/HEIGHT;
            double yFractal=(y- HEIGHT/2) * 2.0/HEIGHT;

            int  iterations= Mandelbrot::getIterations(xFractal,yFractal);

            if(iterations == Mandelbrot::MAX_ITERATIONS){
                histogram[iterations]++;
            }
            histogram[iterations]++;

            uint8_t color =(uint8_t)(256 * (double)iterations/Mandelbrot::MAX_ITERATIONS);

            color=color*color*color;

            bitmap.setPixel(x,y, color,0,0);
            if(color<min) min = color;
            if(color>max) max = color;

        }
    }

    cout<<endl;

    int count=0;
    for(int i=0; i< Mandelbrot::MAX_ITERATIONS;i++){
        cout<<histogram[i]<< " "<<flush;
        count +=histogram[i];
    }
    cout<<count<<"; "<<WIDTH*HEIGHT<<endl;
    cout<<endl;
    cout<<min<<", "<<max<<endl;


    //bitmap.setPixel(WIDTH/2,HEIGHT/2,255,255,255);




    bitmap.write("test.bmp");
    cout << "Finished." << endl;


// 80
    return 0;
}
