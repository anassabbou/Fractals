#include "Sierpinski.h"
#include <random>
#include <algorithm>

namespace fractals {

static inline uint32_t packARGB(unsigned a, unsigned r, unsigned g, unsigned b) {
    return ((a & 0xFFu) << 24) | ((r & 0xFFu) << 16) | ((g & 0xFFu) << 8) | (b & 0xFFu);
}

std::vector<uint32_t> renderSierpinski(const SierpinskiParams& p) {
    std::vector<uint32_t> img(static_cast<size_t>(p.width) * p.height,
                              packARGB(0xFF, 0, 0, 0));

    std::mt19937_64 rng(0xC0FFEE);
    std::uniform_int_distribution<int> pick(0, 2);

    // Start from any point (use centroid of vertices)
    double x = (p.ax + p.bx + p.cx) / 3.0;
    double y = (p.ay + p.by + p.cy) / 3.0;

    auto put = [&](double px, double py) {
        int ix = std::clamp(static_cast<int>(px * p.width), 0, p.width - 1);
        int iy = std::clamp(static_cast<int>((1.0 - py) * p.height), 0, p.height - 1); // y down
        img[static_cast<size_t>(iy) * p.width + ix] = packARGB(0xFF, 255, 255, 255);
    };

    // Throw away a few iterations to settle
    for (int i = 0; i < 10; ++i) {
        switch (pick(rng)) {
            case 0: x = (x + p.ax) * 0.5; y = (y + p.ay) * 0.5; break;
            case 1: x = (x + p.bx) * 0.5; y = (y + p.by) * 0.5; break;
            default:x = (x + p.cx) * 0.5; y = (y + p.cy) * 0.5; break;
        }
    }

    for (int i = 0; i < p.points; ++i) {
        switch (pick(rng)) {
            case 0: x = (x + p.ax) * 0.5; y = (y + p.ay) * 0.5; break;
            case 1: x = (x + p.bx) * 0.5; y = (y + p.by) * 0.5; break;
            default:x = (x + p.cx) * 0.5; y = (y + p.cy) * 0.5; break;
        }
        put(x, y);
    }

    return img;
}

} // namespace fractals
