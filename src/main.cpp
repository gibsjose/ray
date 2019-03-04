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
#include <float.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "camera.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"
#include "lambertian.h"
#include "metal.h"
#include "utilities.h"

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////
int main() {
    const uint32_t width = 1200;            ///< Scene width
    const uint32_t height = 600;            ///< Scene height
    const uint32_t num_samples = 80;        ///< Number of samples over which to average edge colour
    const float gamma = 2.0;                ///< Gamma value
    const float inv_gamma = 1.0 / gamma;    ///< Inverse gamma value

    float aspect_ratio = (float)width / height;

    // Write PPM header
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    // Camera object
    Camera camera;

    // Materials
    Lambertian diffuse_1(vec3(0.8, 0.3, 0.3));
    Lambertian diffuse_2(vec3(0.8, 0.8, 0.0));
    Metal metal_1(vec3(0.8, 0.6, 0.2));
    Metal metal_2(vec3(0.8, 0.8, 0.8));

    // Hittable objects 
    Hittable * list[2];
    list[0] = new Sphere(vec3(0, -100.5, -1), 100, &diffuse_1);
    list[1] = new Sphere(vec3(0, 0, -1), 0.5, &diffuse_2);
    // list[1] = new Sphere(vec3(1, 0, -1), 0.5, &metal_1);
    // list[3] = new Sphere(vec3(-1, 0, -1), 0.5, &metal_2);
    Hittable * world = new HittableList(list, 2);

    // Draw screen starting in the lower left corner
    for (int32_t j = height - 1; j >= 0; --j) {
        for (int32_t i = 0; i < width; ++i) {
            vec3 colour(0, 0, 0);

            // Sample the edge values to perform anti-aliasing
            for (int32_t s = 0; s < num_samples; ++s) {
                float u = float(i + drand48()) / float(width);
                float v = float(j + drand48()) / float(height);

                Ray ray = camera.get_ray(u, v);
                colour += Colour(ray, world, 0);
            }

            colour /= float(num_samples);
            colour = vec3(pow(colour.r(), inv_gamma), pow(colour.g(), inv_gamma), pow(colour.b(), inv_gamma));

            int32_t ir = int32_t(255.99 * colour.r());
            int32_t ig = int32_t(255.99 * colour.g());
            int32_t ib = int32_t(255.99 * colour.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
