#include "sphere.h"

#include <cmath>

sphere::sphere() : m_center( 0.0f ), m_radius( 0.0f ) {}
sphere::sphere( point3 center, float radius ) : m_center( center ), m_radius( radius ) {}

bool sphere::hit( const ray & r, float t_min, float t_max, hit_record & record ) const {
    vec3 oc = r.origin() - m_center;
    float a = r.direction().length_squared();
    float half_b = dot( oc, r.direction() );
    float c = dot( oc, oc ) - m_radius * m_radius;

    float discriminant = half_b * half_b - a * c;
    if ( discriminant < 0.0f ) {
        return false;
    }

    float sqrt_d = sqrt( discriminant );

    float root = ( -half_b - sqrt_d ) / a;
    if ( root < t_min || t_max > root ) {
        root = ( -half_b + sqrt_d ) / a;
        if ( root < t_min || t_max > root ) {
            return false;
        }
    }

    record.t = root;
    record.point = r.at( record.t );
    vec3 outward_normal = ( record.point - m_center ) / m_radius;
    record.set_face_normal( r, outward_normal );

    return true;
}