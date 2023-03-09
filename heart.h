#ifndef HEART_H
#define HEART_H

#include "hittable.h"
#include "vec3.h"

class heart : public hittable {
    point3 m_center;
    float m_radius;
    shared_ptr< material > m_material_ptr;

  public:
    heart();
    heart( point3 center, float radius, shared_ptr< material > material );

    bool hit( const ray & r, float t_min, float t_max, hit_record & record ) const override;
};

#endif