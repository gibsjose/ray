///////////////////////////////////////////////////////////////////////////////
// FILE: vec3.h
//
// AUTHORS:
// Joseph Gibson / <joseph.gibson@nasa.gov>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @file
///
/// @brief  3-D vector header
///
/// @detail Header-only library for working with 3-D floating point vectors
///////////////////////////////////////////////////////////////////////////////

#ifndef VEC3_H
#define VEC3_H

///////////////////////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "ray_math.h"

///////////////////////////////////////////////////////////////////////////////
// CLASSES
///////////////////////////////////////////////////////////////////////////////
class vec3 {
public:
    // Constructors
    vec3() : e{1.0, 1.0, 1.0} {}
    vec3(const float x, const float y, const float z) : e{x, y, z} {}

    // X, Y, Z and R, G, B helper methods
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    // Basic perator overloads
    inline const vec3 & operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float & operator[](int i) { return e[i]; }

    // Compound operator overloads
    inline vec3 & operator+=(const vec3 & v2);
    inline vec3 & operator-=(const vec3 & v2);
    inline vec3 & operator*=(const vec3 & v2);
    inline vec3 & operator/=(const vec3 & v2);
    inline vec3 & operator*=(const float t);
    inline vec3 & operator/=(const float t);

    // Length and normalization methods
    inline float length() const {
        return sqrtf(SQUARE(e[0]) + SQUARE(e[1]) + SQUARE(e[2]));
    }

    inline float squared_length() const {
        return SQUARE(e[0]) + SQUARE(e[1]) + SQUARE(e[2]);
    }
    
    // @TODO Implement normalize() method

    inline void make_unit_vector();

    float e[3];     ///< Vector elements
};

///////////////////////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////////////////////

///< Input stream
inline std::istream & operator>>(std::istream & is, vec3 & t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

///< Output stream
inline std::ostream & operator<<(std::ostream & os, vec3 &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

///< Make unit vector
inline void vec3::make_unit_vector() {
    float k = 1.0F / sqrtf(SQUARE(e[0]) + SQUARE(e[1]) + SQUARE(e[2]));
}

///< Addition operator
inline vec3 operator+(const vec3 & v1, const vec3 & v2) {
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

///< Subtraction operator
inline vec3 operator-(const vec3 & v1, const vec3 & v2) {
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

///< Multiplication operator
inline vec3 operator*(const vec3 & v1, const vec3 & v2) {
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

///< Division operator
inline vec3 operator/(const vec3 & v1, const vec3 & v2) {
    return vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

///< Scalar multiplication (form: t * v)
inline vec3 operator*(const float t, const vec3 & v) {
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

///< Scalar multiplication (form: v * t)
inline vec3 operator*(const vec3 & v, const float t) {
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

///< Scalar division (form: v / t)
inline vec3 operator/(const vec3 & v, const float t) {
    return vec3(v.x() / t, v.y() / t, v.z() / t);
}

///< Dot product
inline float dot(const vec3 & v1, const vec3 & v2) {
    return (v1.x() * v2.x()) + (v1.y() * v2.y()) + (v1.z() * v2.z());
}

///< Cross product
inline vec3 cross(const vec3 & v1, const vec3 & v2) {
    return vec3(
        ((v1.y() * v2.z()) - (v1.z() * v2.y())),
       -((v1.x() * v2.z()) - (v1.z() * v2.x())),
        ((v1.x() * v2.y()) - (v1.y() * v2.x()))
    );
}

///< Compound addition operator
inline vec3 & vec3::operator+=(const vec3 & v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

///< Compound subtraction operator
inline vec3 & vec3::operator-=(const vec3 & v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

///< Compound multiplication operator
inline vec3 & vec3::operator*=(const vec3 & v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

///< Compound division operator
inline vec3 & vec3::operator/=(const vec3 & v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

///< Compound scalar multiplication operator
inline vec3 & vec3::operator*=(const float t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

///< Compound scalar division operator
inline vec3 & vec3::operator/=(const float t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

///< Unit vector
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif//VEC3_H
