///////////////////////////////////////////////////////////////////////////////
// FILE: utilities.h
//
// AUTHORS:
// Joseph Gibson / <joseph.gibson@nasa.gov>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @file
///
/// @brief  Utilities
///////////////////////////////////////////////////////////////////////////////

#ifndef UTILITIES_H
#define UTILITIES_H

///////////////////////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////////////////////
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////
vec3 RandomInUnitSphere();
vec3 Colour(const Ray & ray, Hittable * world, int32_t depth);
vec3 Reflect(const vec3 & v, const vec3 & n);
bool Refract(const vec3 & v, const vec3 & n, const float ratio, vec3 & refracted);

#endif//UTILITIES_H
