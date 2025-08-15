#pragma once
#include <vector>
#include <cstdint>

namespace fractals {

struct SierpinskiParams {
    int width  = 800;
    int height = 600;
    int points = 200000;   // number of chaos-game iterations
    // Triangle vertices (normalized to [0,1] x [0,1] then scaled to image):
    double ax = 0.5,  ay = 0.98;
    double bx = 0.02, by = 0.02;
    double cx = 0.98, cy = 0.02;
};

std::vector<uint32_t> renderSierpinski(const SierpinskiParams& p);

}
