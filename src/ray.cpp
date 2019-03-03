///////////////////////////////////////////////////////////////////////////////
// FILE: ray.cpp
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
#include "vec3.h"
#include "ray.h"

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////
vec3 Ray::colour() {
    float t = this->hit_sphere(vec3(0, 0, -1), 0.5);
    
    if (t > 0) {
        vec3 N = unit_vector(this->point_at_parameter(t) - vec3(0, 0, -1));
        return 0.5 * vec3(N.x() + 1.0, N.y() + 1.0, N.z() + 1.0);
    }

    vec3 unit_direction = unit_vector(this->direction());
    t = 0.5F * (unit_direction.y() + 1.0);
    return ((1.0 - t) * vec3(1, 1, 1)) + (t * vec3(0.5, 0.7, 1.0));
}

float Ray::hit_sphere(const vec3 & centre, const float radius) {
    vec3 oc = this->origin() - centre;

    float a = dot(this->direction(), this->direction());
    float b = 2.0 * dot(oc, this->direction());
    float c = dot(oc, oc) - SQUARE(radius);
    float discriminant = SQUARE(b) - (4 * a * c);
    
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrtf(discriminant)) / (2.0 * a);
    }
}
