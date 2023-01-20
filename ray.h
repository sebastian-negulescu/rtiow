#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    point3 m_origin;
    vec3 m_direction;

  public:
    ray();
    ray( const point3 & origin, const vec3 & direction );

    point3 origin() const;
    vec3 direction() const;

    point3 at( float t ) const;
};

#endif