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
        vec3 outward_normal;
        vec3 reflected = Reflect(ray.direction(), record.normal);

        vec3 refracted;
        float refraction_ratio;
        attenuation = vec3(1.0, 1.0, 1.0);  ///< Attenuation is always 1; the glass surface absorbs nothing

        // Set the refraction ratio (based on index of air = 1.0)
        if (dot(ray.direction(), record.normal) > 0) {
            outward_normal = -record.normal;
            refraction_ratio = refraction_index;
        } else {
            outward_normal = record.normal;
            refraction_ratio = 1.0 / refraction_index;
        }

        // Refract
        if (Refract(ray.direction(), outward_normal, refraction_ratio, refracted)) {
            scattered = Ray(record.p, refracted);
        } else {
            scattered = Ray(record.p, reflected);
        }

        return true;
    }

    float refraction_index;     ///< Index of refraction
};

#endif//DIELECTRIC_H
