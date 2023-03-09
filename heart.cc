#include "heart.h"

#include <cmath>
#include <gsl/gsl_poly.h>

heart::heart() : m_center( 0.0f ), m_radius( 0.0f ) {}
heart::heart( point3 center, float radius, shared_ptr< material > material )
    : m_center( center ), m_radius( radius ), m_material_ptr( material ) {}

bool heart::hit( const ray & r, float t_min, float t_max, hit_record & record ) const {
    point3 origin = r.origin();
    float ox = origin.x();
    float oy = origin.y();
    float oz = origin.z();

    vec3 direction = r.direction();
    float dx = direction.x();
    float dy = direction.y();
    float dz = direction.z();

    return true;
}