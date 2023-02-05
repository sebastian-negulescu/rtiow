#ifndef HITTABLE_H
#define HITTABLE_H

#include "helpers.h"
#include "ray.h"
#include "vec3.h"

class material;

struct hit_record {
    point3 point;
    vec3 normal;
    shared_ptr<material> material_ptr;
    float t;
    bool front_face;

    // function to make normal always point against the ray
    inline void set_face_normal( const ray & r, const vec3 & outward_normal ) {
        front_face = dot( r.direction(), outward_normal ) < 0.0f;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
  public:
    virtual bool hit( const ray & r, float t_min, float t_max, hit_record & record ) const = 0;
};

#endif