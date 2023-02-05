#ifndef CAMERA_H
#define CAMERA_H

#include "helpers.h"
#include "ray.h"
#include "vec3.h"

class camera {
    point3 m_origin;
    point3 m_lower_left_corner;
    vec3 m_horizontal;
    vec3 m_vertical;

  public:
    camera( 
        point3 lookfrom,
        point3 lookat,
        vec3 vup,
        float vfov, 
        float aspect_ratio
    );

    ray get_ray( float s, float t ) const;

};

#endif