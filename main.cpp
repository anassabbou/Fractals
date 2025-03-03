#include <iostream>
#include "Bitmap/Bitmap.h"
#include "Mandelbrot/Mandelbrot.h"
#include "Mandelbrot/Julia.h"
#include "Mandelbrot/BurningShip.h"
#include "Mandelbrot/Sierpinski.h"

#include <cstdint>
#include <memory>
#include <cmath>

using namespace abbouspace;
using namespace std;

double calculateHue(int iterations, unique_ptr<int[]>& histogram, int total) {
    double hue = 0.0;
    for (int i = 0; i <= iterations; i++) {
        hue += static_cast<double>(histogram[i]) / total;
    }
    return hue;
}

void setPixelColor(Bitmap& bitmap, int x, int y, int iterations, unique_ptr<int[]>& histogram, int total) {
    uint8_t red = 0, green = 0, blue = 0;
    if (iterations != Mandelbrot::MAX_ITERATIONS) {
        double hue = calculateHue(iterations, histogram, total);
        red = std::min(static_cast<uint8_t>(pow(3, hue * 2)), static_cast<uint8_t>(255));
        green = std::min(static_cast<uint8_t>(pow(60, hue * 1.6)), static_cast<uint8_t>(255));
        blue = std::min(static_cast<uint8_t>(pow(200, hue)), static_cast<uint8_t>(255));
    }
    bitmap.setPixel(x, y, red, green, blue);
}

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    Bitmap bitmap(WIDTH, HEIGHT);

    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{0});
    unique_ptr<int[]> histogramJulia(new int[Julia::MAX_ITERATIONS]{0});
    unique_ptr<int[]> histogramBurningShip(new int[BurningShip::MAX_ITERATIONS]{0});
    unique_ptr<int[]> histogramSierpinski(new int[Sierpinski::MAX_ITERATIONS]{0});
    unique_ptr<int[]> fractal(new int[WIDTH * HEIGHT]{0});

    double xMoving = 150, yMoving = 2;
    double yZoom = HEIGHT - 130, xZoom = HEIGHT - 60;

    Julia julia;
    BurningShip burningShip;
    Sierpinski sierpinski;


    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractal = ((x - WIDTH / 2) - xMoving) * 2.0 / xZoom;
            double yFractal = (y - HEIGHT / 2 + yMoving) * 2.0 / yZoom;

            int iterationsMandelbrot = Mandelbrot::getIterations(xFractal, yFractal);
            
            int iterationsJulia = julia.getIterations(xFractal, yFractal);
            int iterationsBurningShip = burningShip.getIterations(xFractal, yFractal);
            int iterationsSierpinski = sierpinski.getIterations(xFractal, yFractal);

            fractal[y * WIDTH + x] = iterationsMandelbrot;

            if (iterationsMandelbrot != Mandelbrot::MAX_ITERATIONS) {
                histogram[iterationsMandelbrot]++;
            }
            if (iterationsJulia != Julia::MAX_ITERATIONS) {
                histogramJulia[iterationsJulia]++;
            }
            if (iterationsBurningShip != BurningShip::MAX_ITERATIONS) {
                histogramBurningShip[iterationsBurningShip]++;
            }
            if (iterationsSierpinski != Sierpinski::MAX_ITERATIONS) {
                histogramSierpinski[iterationsSierpinski]++;
            }
        }
    }

    int total = 0;
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        total += histogram[i];
    }

    // Generate image for Mandelbrot
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            setPixelColor(bitmap, x, y, fractal[y * WIDTH + x], histogram, total);
        }
    }
    bitmap.write("generated_images/test_mandelbrot.bmp");


    // Generate image for Julia
    Bitmap bitmapJulia(WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractalJulia = ((x - WIDTH / 2) - xMoving) * 2.0 / xZoom;
            double yFractalJulia = (y - HEIGHT / 2 + yMoving) * 2.0 / yZoom;
            int iterations = julia.getIterations(xFractalJulia, yFractalJulia);
            setPixelColor(bitmapJulia, x, y, iterations, histogramJulia, total);
        }
    }
    bitmapJulia.write("generated_images/test_julia.bmp");


    // Generate image for Burning Ship
    Bitmap bitmapBurningShip(WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractalBurningShip = ((x - WIDTH / 2) - xMoving) * 2.0 / xZoom;
            double yFractalBurningShip = (y - HEIGHT / 2 + yMoving) * 2.0 / yZoom;
            int iterations = burningShip.getIterations(xFractalBurningShip, yFractalBurningShip);
            setPixelColor(bitmapBurningShip, x, y, iterations, histogramBurningShip, total);
        }
    }
    bitmapBurningShip.write("generated_images/test_burning_ship.bmp");


    // Generate image for Sierpinski
    Bitmap bitmapSierpinski(WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double xFractalSierpinski = ((x - WIDTH / 2) - xMoving) * 2.0 / xZoom;
            double yFractalSierpinski = (y - HEIGHT / 2 + yMoving) * 2.0 / yZoom;
            int iterations = sierpinski.getIterations(xFractalSierpinski, yFractalSierpinski);
            uint8_t red = 255, green = 255, blue = 255; // Color for Sierpinski
            if (iterations != Sierpinski::MAX_ITERATIONS) {
                bitmapSierpinski.setPixel(x, y, red, green, blue);
            }
        }
    }
    bitmapSierpinski.write("generated_images/test_sierpinski.bmp");


    cout << "Finished." << endl;

    return 0;
}
