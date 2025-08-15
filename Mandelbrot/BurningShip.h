#pragma once
#include <vector>
#include <cstdint>

namespace fractals {

struct BurningShipParams {
    int width  = 800;
    int height = 600;
    int maxIters = 500;
    // View window in the complex plane:
    double xMin = -2.2, xMax = 1.2;
    double yMin = -2.0, yMax = 1.2;
};

std::vector<uint32_t> renderBurningShip(const BurningShipParams& p);

}
