cmake_minimum_required(VERSION 3.23)
project(Fractals)

set(CMAKE_CXX_STANDARD 14)

add_executable(Fractals main.cpp BitmapFileHeader.h BitmapInfoHeader.h Bitmap.cpp Bitmap.h Mandelbrot.cpp Mandelbrot.h)
