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

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////
vec3 RandomInUnitSphere();
vec3 Colour(const Ray & ray, Hittable * world);

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

    // Hittable objects 
    Hittable * list[2];
    list[0] = new Sphere(vec3(0, -100.5, -1), 100);
    list[1] = new Sphere(vec3(0, 0, -1), 0.5);
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
                colour += Colour(ray, world);
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

// Generate a random vector in a unit sphere
vec3 RandomInUnitSphere() {
    vec3 p(1, 1, 1);

    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);

    return p;
}

// Generate a colour given a ray and a list of hittable objects
vec3 Colour(const Ray & ray, Hittable * world) {
    HitRecord record;

    // Check for a hit using the input ray
    // NOTE: t_min is set to 0.001 instead of 0 to avoid the 'shadow acne problem'
    //       by ignoring hits very near zero
    if (world->hit(ray, 0.001, MAXFLOAT, record)) {
        vec3 target = record.p + record.normal + RandomInUnitSphere();
        return 0.5 * Colour(Ray(record.p, target - record.p), world);
    } else {
        vec3 unit_direction = unit_vector(ray.direction());
        float t = 0.5F * (unit_direction.y() + 1.0);
        return ((1.0 - t) * vec3(1, 1, 1)) + (t * vec3(0.5, 0.7, 1.0));
    }
}
