//
// Created by Anass on 2/6/2024.
//

#ifndef FRACTALS_BITMAP_H
#define FRACTALS_BITMAP_H
#include <string>
#include <cstdint>
#include <memory>

using namespace std;

namespace abbouspace {

    class Bitmap {
    private:
        int m_width{0};
        int m_height{0};
        unique_ptr<uint8_t[]> m_pPixel{nullptr};

    public:

        Bitmap(int width, int height);
        void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);//255bits
        bool write(string filename);

        virtual ~Bitmap();
    };

} // abbouspace

#endif //FRACTALS_BITMAP_H
