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
#include "utilities.h"

///////////////////////////////////////////////////////////////////////////////
// CLASSES
///////////////////////////////////////////////////////////////////////////////
class Camera {
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief  Camera constructor
    ///
    /// @param  look_from - The vector from we are looking from (new origin)
    /// @param  look_at - The vector to where we are looking at
    /// @param  vup - View up ('vup') vector
    /// @param  vertical_fov - Top-to-bottom field of view in degrees
    /// @param  aspect_ratio - Ratio of width to height
    /// @param  aperture - The aperture setting
    /// @param  focal_distance - The focal distance in pixels
    ///////////////////////////////////////////////////////////////////////////
    Camera(const vec3 & look_from, const vec3 & look_at, const vec3 & vup, const float vertical_fov, const float aspect_ratio, const float aperture, const float focal_distance) {
        // Convert FOV to radians
        float theta = vertical_fov * M_PI / 180.0;

        lens_radius = aperture / 2.0;

        vec3 u;
        vec3 v;
        vec3 w;

        float half_height = tan(theta / 2.0);
        float half_width = aspect_ratio * half_height;

        origin = look_from;

        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        lower_left_corner = origin - (half_width * focal_distance * u) - (half_height * focal_distance * v) - (focal_distance * w);
        horizontal = 2.0 * half_width * focal_distance * u;
        vertical = 2.0 * half_height * focal_distance * v;
    }

    Ray get_ray(const float s, const float t) {
        vec3 disk = lens_radius * RandomInUnitDisk();
        vec3 offset = (u * disk.x()) + (v * disk.y());
        return Ray(origin + offset, lower_left_corner + (s * horizontal) + (t * vertical) - origin - offset);
    }

    vec3 origin;                ///< Origin
    vec3 lower_left_corner;     ///< Lower left corner of the scene
    vec3 horizontal;            ///< Horizontal axis
    vec3 vertical;              ///< Vertical axis
    float lens_radius;          ///< Lens radius in pixels
    vec3 u;                     ///< X axis vector
    vec3 v;                     ///< Y axis vector
    vec3 w;                     ///< Z axis vector
};

#endif//CAMERA_H
