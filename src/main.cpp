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
#include "dielectric.h"
#include "utilities.h"

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////
Hittable * RandomScene();

int main() {
    const uint32_t width = 600;                 ///< Scene width
    const uint32_t height = 400;                ///< Scene height
    const uint32_t num_samples = 20;            ///< Number of samples over which to average edge colour
    const float gamma = 2.0;                    ///< Gamma value
    const float inv_gamma = 1.0 / gamma;        ///< Inverse gamma value
    const uint8_t PNG_RGB_CHANNELS = 3;         ///< Number of channels for PNG: 3 for RGB, 4 for RGBA

    // Camera settings
    const vec3 look_from(14, 3, 12);                                ///< Look-from vector (origin)
    const vec3 look_at(0, 0, 0);                                    ///< Look-at vector
    const vec3 vup(0, 1, 0);                                        ///< View up
    const float aspect_ratio = (float)width / height;               ///< Aspect ratio
    const float vertical_fov = 20.0;                                ///< Vertical field of view in degrees (default = 90.0)
    const float aperture = 0.1;                                     ///< Aperture
    const float focal_distance = 13.0;                              ///< Focal distance

    uint8_t * image_data = NULL;

    // Allocate memory for the image
    image_data = (uint8_t *) malloc(width * height * PNG_RGB_CHANNELS);

    // Camera object
    Camera camera(look_from, look_at, vup, vertical_fov, aspect_ratio, aperture, focal_distance);

    // Materials
    Lambertian diffuse_1(vec3(0.1, 0.2, 0.5));
    Lambertian diffuse_2(vec3(0.8, 0.8, 0.0));
    Metal metal_1(vec3(0.8, 0.6, 0.2), 0.3);
    Metal metal_2(vec3(0.8, 0.8, 0.8), 1.0);
    Dielectric dielectric_1(1.5);

    // Hittable objects 
    Hittable * list[4];

    list[0] = new Sphere(vec3(0,-1000,0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5)));
    list[1] = new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5));
    list[2] = new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.8, 0.8, 0.0)));
    list[3] = new Sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5), 0.0));

    Hittable * world = new HittableList(list, 4);

    // world = RandomScene();

    const float inv_width = 1.0 / float(width);
    const float inv_height = 1.0 / float(height);

    // Draw screen starting in the lower left corner
    for (int32_t j = height - 1; j >= 0; --j) {
        for (int32_t i = 0; i < width; ++i) {
            vec3 colour(0, 0, 0);

            // Sample the edge values to perform anti-aliasing
            for (int32_t s = 0; s < num_samples; ++s) {
                float u = float(i + drand48()) * inv_width;
                float v = float(j + drand48()) * inv_height;

                Ray ray = camera.get_ray(u, v);
                colour += Colour(ray, world, 0);
            }

            colour /= float(num_samples);
            colour = vec3(pow(colour.r(), inv_gamma), pow(colour.g(), inv_gamma), pow(colour.b(), inv_gamma));
            // colour = vec3(sqrt(colour.r()), sqrt(colour.g()), sqrt(colour.b()));

            int32_t ir = int32_t(255.99 * colour.r());
            int32_t ig = int32_t(255.99 * colour.g());
            int32_t ib = int32_t(255.99 * colour.b());

            uint32_t y = (height - 1 - j) * PNG_RGB_CHANNELS;
            uint32_t x = i * PNG_RGB_CHANNELS;

            uint32_t r_index = (y * width) + x + 0;
            uint32_t g_index = (y * width) + x + 1;
            uint32_t b_index = (y * width) + x + 2;

            image_data[r_index] = (uint8_t)ir;
            image_data[g_index] = (uint8_t)ig;
            image_data[b_index] = (uint8_t)ib;
        }
    }

    // Write PNG
    stbi_write_png("scene.png", width, height, PNG_RGB_CHANNELS, image_data, width * PNG_RGB_CHANNELS);

    // Free the image data
    free(image_data);
}

Hittable * RandomScene() {
    int32_t n = 500;
    Hittable ** list = new Hittable * [n + 1];
    list[0] =  new Sphere(vec3(0,-1000,0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5)));
    int32_t i = 1;
    for (int32_t a = -11; a < 11; a++) {
        for (int32_t b = -11; b < 11; b++) {
            float material = drand48();
            vec3 centre(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48()); 
            if ((centre - vec3(4, 0.2, 0)).length() > 0.9) {
                // Diffuse 
                if (material < 0.8) {
                    list[i++] = new Sphere(centre, 0.2, new Lambertian(vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
                }

                // Metal
                else if (material < 0.95) {
                    list[i++] = new Sphere(centre, 0.2,
                            new Metal(vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())),  0.5 * drand48()));
                }
                
                // Glass
                else {
                    list[i++] = new Sphere(centre, 0.2, new Dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new HittableList(list, i);
}
