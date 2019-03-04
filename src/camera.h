///////////////////////////////////////////////////////////////////////////////
// FILE: camera.h
//
// AUTHORS:
// Joseph Gibson / <joseph.gibson@nasa.gov>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @file
///
/// @brief  Camera class
///////////////////////////////////////////////////////////////////////////////

#ifndef CAMERA_H
#define CAMERA_H

///////////////////////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////////////////////
#include "ray.h"

///////////////////////////////////////////////////////////////////////////////
// CLASSES
///////////////////////////////////////////////////////////////////////////////
class Camera {
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief  Camera constructor
    ///
    /// @param  vertical_fov - Top-to-bottom field of view in degrees
    /// @param  aspect_ratio - Ratio of width to height
    ///////////////////////////////////////////////////////////////////////////
    Camera(const float vertical_fov, const float aspect_ratio) {
        // Convert FOV to radians
        float theta = vertical_fov * M_PI / 180.0;

        float half_height = tan(theta / 2.0);
        float half_width = aspect_ratio * half_height;

        origin = vec3(0, 0, 0);
        lower_left_corner = vec3(-half_width, -half_height, -1.0);
        horizontal = vec3(2.0 * half_width, 0, 0);
        vertical = vec3(0, 2.0 * half_height, 0);
    }

    Ray get_ray(const float u, const float v) {
        return Ray(origin, lower_left_corner + (u * horizontal) + (v * vertical) - origin);
    }

    vec3 origin;                ///< Origin
    vec3 lower_left_corner;     ///< Lower left corner of the scene
    vec3 horizontal;            ///< Horizontal axis
    vec3 vertical;              ///< Vertical axis
};

#endif//CAMERA_H
