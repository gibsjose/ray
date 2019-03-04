///////////////////////////////////////////////////////////////////////////////
// FILE: utilities.cpp
//
// AUTHORS:
// Joseph Gibson / <joseph.gibson@nasa.gov>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @file
///
/// @brief  Utilities
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////////////////////
#include "utilities.h"
#include "material.h"

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////
// Generate a random vector in a unit sphere
vec3 RandomInUnitSphere() {
    vec3 p(1, 1, 1);

    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);

    return p;
}

// Generate a colour given a ray and a list of hittable objects
vec3 Colour(const Ray & ray, Hittable * world, int32_t depth) {
    HitRecord record;

    // Check for a hit using the input ray
    // NOTE: t_min is set to 0.001 instead of 0 to avoid the 'shadow acne problem'
    //       by ignoring hits very near zero
    if (world->hit(ray, 0.001, MAXFLOAT, record)) {
        Ray scattered;
        vec3 attenuation;

        if ((depth < 50) && record.material->scatter(ray, record, attenuation, scattered)) {
            return attenuation * Colour(scattered, world, depth + 1);
        } else {
            return vec3(0, 0, 0);
        }
    } else {
        vec3 unit_direction = unit_vector(ray.direction());
        float t = 0.5F * (unit_direction.y() + 1.0);
        return ((1.0 - t) * vec3(1, 1, 1)) + (t * vec3(0.5, 0.7, 1.0));
    }
}

// Compute the reflection between two vectors
vec3 Reflect(const vec3 & v, const vec3 & n) {
    return v - 2 * dot(v, n) * n;
}

// Compute the refraction between two vectors, given the ratio (ni / nt) of the indices of refraction
// between the two materials
bool Refract(const vec3 & v, const vec3 & n, const float ratio, vec3 & refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - (SQUARE(ratio) * (1.0 - SQUARE(dt)));

    if (discriminant > 0) {
        refracted = ratio * (uv - (n * dt)) - (n * sqrt(discriminant));
        return true;
    } else {
        return false;
    }
}

// Compute the probability of reflection using Schlick's polynomial approximation
float Schlick(const float cosine, const float refraction_index) {
    float r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
    r0 = SQUARE(r0);
    return r0 + ((1.0 - r0) * pow((1.0 - cosine), 5));
}
