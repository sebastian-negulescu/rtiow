#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    point3 point;
    vec3 normal;
    float t;
};

class hittable {
  public:
    virtual bool hit( const ray & r, float t_min, float t_max, hit_record & record ) const = 0;
};

#endif