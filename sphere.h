#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    point3 m_center;
    float m_radius;
  
  public:
    sphere();
    sphere( point3 center, float radius );

    bool hit( const ray & r, float t_min, float t_max, hit_record & record ) const override;
};

#endif