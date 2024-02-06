//
// Created by Anass on 2/6/2024.
//

#ifndef FRACTALS_BITMAPFILEHEADER_H
#define FRACTALS_BITMAPFILEHEADER_H
#include <cstdint>

using namespace std;
#pragma pack(2)
namespace abbouspace {
    struct BitmapFileHeader {
        char header[2]{'B', 'M'};
        int32_t fileSize;
        int32_t reserved{0};
        int32_t dataOffset;
    };
}

#endif //FRACTALS_BITMAPFILEHEADER_H
