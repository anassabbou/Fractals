cmake_minimum_required(VERSION 3.23)
project(Fractals)

set(CMAKE_CXX_STANDARD 14)

add_executable(Fractals main.cpp Bitmap/BitmapFileHeader.h Bitmap/BitmapInfoHeader.h Bitmap/Bitmap.cpp Bitmap/Bitmap.h Mandelbrot/Mandelbrot.cpp Mandelbrot/Mandelbrot.h Mandelbrot/Julia.cpp)
