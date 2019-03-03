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
vec3 ray::colour() {
    float t = this->hit_sphere(vec3(0, 0, -1), 0.5F);
    
    if (t > 0.0F) {
        vec3 N = unit_vector(this->point_at_parameter(t) - vec3(0.0, 0.0, -1.0));
        return 0.5F * vec3(N.x() + 1.0F, N.y() + 1.0F, N.z() + 1.0F);
    }

    vec3 unit_direction = unit_vector(this->direction());
    t = 0.5F * (unit_direction.y() + 1.0F);
    return ((1.0F - t) * vec3(1.0F, 1.0F, 1.0F)) + (t * vec3(0.5F, 0.7F, 1.0F));
}

float ray::hit_sphere(const vec3 & centre, const float radius) {
    vec3 oc = this->origin() - centre;

    float a = dot(this->direction(), this->direction());
    float b = 2.0F * dot(oc, this->direction());
    float c = dot(oc, oc) - SQUARE(radius);
    float discriminant = SQUARE(b) - (4 * a * c);
    
    if (discriminant < 0.0F) {
        return -1.0F;
    } else {
        return (-b - sqrtf(discriminant)) / (2.0F * a);
    }
}
