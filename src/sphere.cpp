///////////////////////////////////////////////////////////////////////////////
// FILE: sphere.cpp
//
// AUTHORS:
// Joseph Gibson / <joseph.gibson@nasa.gov>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @file
///
/// @brief  Defines a sphere object
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////////////////////
#include "sphere.h"

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////
bool Sphere::hit(const Ray & ray, const float t_min, const float t_max, HitRecord & record) const {
    vec3 oc = ray.origin() - centre;

    // Vector equation of a sphere
    float a = dot(ray.direction(), ray.direction());
    float b = dot(oc, ray.direction());
    float c = dot(oc, oc) - SQUARE(radius);

    // Compute the descriminant
    float discriminant = SQUARE(b) - (a * c);

    // Sphere was hit if the descriminant is positive
    if (discriminant > 0) {
        float temp = 0.0;
        
        // Check both positive and negative roots
        temp = (-b - sqrt(SQUARE(b) - (a * c))) / a;
        if ((temp < t_max) && (temp > t_min)) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - centre) / radius;
            return true;
        }

        temp = (-b + sqrt(SQUARE(b) - (a * c))) / a;
        if ((temp < t_max) && (temp > t_min)) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - centre) / radius;
            return true;
        }
    }

    // Not hit if the desciminant is zero or negative
    return false;
}
