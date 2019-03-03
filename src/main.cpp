///////////////////////////////////////////////////////////////////////////////
// FILE: main.cpp
//
// AUTHORS:
// Joseph Gibson / <joseph.gibson@nasa.gov>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @file
///
/// @brief  Ray tracer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"
#include "ray.h"

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////
int main() {
    int32_t nx = 800;
    int32_t ny = 400;

    // Write PPM header
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // Screen bounds
    vec3 lower_left_corner(-2.0F, -1.0F, -1.0F);
    vec3 horizontal(4.0F, 0.0F, 0.0F);
    vec3 vertical(0.0F, 2.0F, 0.0F);
    vec3 origin(0.0F, 0.0F, 0.0F);

    for (int32_t j = ny - 1; j >= 0; --j) {
        for (int32_t i = 0; i < nx; ++i) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            ray r(origin, lower_left_corner + (u * horizontal) + (v * vertical));

            vec3 colour = r.colour();

            int32_t ir = int32_t(255.99F * colour.r());
            int32_t ig = int32_t(255.99F * colour.g());
            int32_t ib = int32_t(255.99F * colour.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
