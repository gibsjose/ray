///////////////////////////////////////////////////////////////////////////////
// FILE: dielectric.h
//
// AUTHORS:
// Joseph Gibson / <joseph.gibson@nasa.gov>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @file
///
/// @brief  Dielectric material class
///////////////////////////////////////////////////////////////////////////////

#ifndef DIELECTRIC_H
#define DIELECTRIC_H

///////////////////////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////////////////////
#include "material.h"
#include "utilities.h"

///////////////////////////////////////////////////////////////////////////////
// CLASSES
///////////////////////////////////////////////////////////////////////////////
class Dielectric : public Material {
public:
    Dielectric(const float r) : refraction_index(r) {}

    virtual bool scatter(const Ray & ray, const HitRecord & record, vec3 & attenuation, Ray & scattered) const {
        // Attenuation is always 1; the glass surface absorbs nothing
        attenuation = vec3(1.0, 1.0, 1.0);

        vec3 outward_normal;
        vec3 reflected = Reflect(ray.direction(), record.normal);
        
        vec3 refracted;
        float refraction_ratio;
        float reflection_probability;
        float cosine;

        // Set the refraction ratio (based on index of air = 1.0)
        if (dot(ray.direction(), record.normal) > 0) {
            outward_normal = -record.normal;
            refraction_ratio = refraction_index;
            cosine = refraction_index * dot(ray.direction(), record.normal) / ray.direction().length();
        } else {
            outward_normal = record.normal;
            refraction_ratio = 1.0 / refraction_index;
            cosine = -dot(ray.direction(), record.normal) / ray.direction().length();
        }

        // Refract
        if (Refract(ray.direction(), outward_normal, refraction_ratio, refracted)) {
            reflection_probability = Schlick(cosine, refraction_index);
        } else {
            reflection_probability = 1.0;   // Force reflection
        }

        // Roll a random number to reflect or refract
        if (drand48() < reflection_probability) {
            scattered = Ray(record.p, reflected);
        } else {
            scattered = Ray(record.p, refracted);
        }

        return true;
    }

    float refraction_index;     ///< Index of refraction
};

#endif//DIELECTRIC_H
