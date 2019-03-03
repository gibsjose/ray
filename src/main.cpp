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

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////
vec3 Colour(const Ray & ray, Hittable * world);

int main() {
    const uint32_t width = 800;
    const uint32_t height = 400;

    float aspect_ratio = (float)width / height;

    // Write PPM header
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    // Screen bounds
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(2.0 * aspect_ratio, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    // Objects 
    Hittable * list[2];
    list[0] = new Sphere(vec3(0, -100.5, -1), 100);
    list[1] = new Sphere(vec3(0, 0, -1), 0.5);
    Hittable * world = new HittableList(list, 2);

    // Draw screen starting in the lower left corner
    for (int32_t j = height - 1; j >= 0; --j) {
        for (int32_t i = 0; i < width; ++i) {
            float u = float(i) / float(width);
            float v = float(j) / float(height);

            Ray ray(origin, lower_left_corner + (u * horizontal) + (v * vertical));

            vec3 p = ray.point_at_parameter(2.0);
            vec3 colour = Colour(ray, world);

            int32_t ir = int32_t(255.99 * colour.r());
            int32_t ig = int32_t(255.99 * colour.g());
            int32_t ib = int32_t(255.99 * colour.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}

vec3 Colour(const Ray & ray, Hittable * world) {
    HitRecord record;

    if (world->hit(ray, 0.0, MAXFLOAT, record)) {
        return 0.5 * vec3(record.normal.x() + 1.0, record.normal.y() + 1.0, record.normal.z() + 1.0);
    } else {
        vec3 unit_direction = unit_vector(ray.direction());
        float t = 0.5F * (unit_direction.y() + 1.0);
        return ((1.0 - t) * vec3(1, 1, 1)) + (t * vec3(0.5, 0.7, 1.0));
    }
}
