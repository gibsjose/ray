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

// Compute the reflection between two vectors
vec3 Reflect(const vec3 & v, const vec3 & n) {
    return v - 2 * dot(v, n) * n;
}
