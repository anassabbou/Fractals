#include "BurningShip.h"
#include <cmath>
#include <algorithm>

namespace fractals {

static inline uint32_t packARGB(unsigned a, unsigned r, unsigned g, unsigned b) {
    return ((a & 0xFFu) << 24) | ((r & 0xFFu) << 16) | ((g & 0xFFu) << 8) | (b & 0xFFu);
}

static inline uint32_t gradient(double t) {
    t = std::clamp(t, 0.0, 1.0);
    double r = 9.0 * (1.0 - t) * t * t * t * 255.0;
    double g = 15.0 * (1.0 - t) * (1.0 - t) * t * t * 255.0;
    double b = 8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t * 255.0;
    return packARGB(0xFF, (unsigned)r, (unsigned)g, (unsigned)b);
}

std::vector<uint32_t> renderBurningShip(const BurningShipParams& p) {
    std::vector<uint32_t> img(static_cast<size_t>(p.width) * p.height, 0);
    const double dx = (p.xMax - p.xMin) / (p.width  - 1);
    const double dy = (p.yMax - p.yMin) / (p.height - 1);

    for (int j = 0; j < p.height; ++j) {
        const double cy = p.yMax - j * dy; // top->bottom
        for (int i = 0; i < p.width; ++i) {
            const double cx = p.xMin + i * dx;

            double zx = 0.0, zy = 0.0; // z0 = 0
            int iter = 0;
            while (zx*zx + zy*zy < 4.0 && iter < p.maxIters) {
                double x = std::fabs(zx);
                double y = std::fabs(zy);
                double xt = x*x - y*y + cx;
                double yt = 2.0 * x * y + cy;
                zx = xt;
                zy = yt;
                ++iter;
            }

            size_t idx = static_cast<size_t>(j) * p.width + i;

            if (iter >= p.maxIters) {
                img[idx] = packARGB(0xFF, 0, 0, 0); // inside set -> black
            } else {
                double mag2 = zx*zx + zy*zy;
                double nu = std::log2(std::log(std::max(mag2, 1e-300)) / std::log(2.0));
                double smooth = (iter + 1 - nu) / p.maxIters;
                img[idx] = gradient(smooth);
            }
        }
    }
    return img;
}

} // namespace fractals
