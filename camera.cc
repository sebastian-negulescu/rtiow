#include "camera.h"

camera::camera( 
    point3 lookfrom,
    point3 lookat,
    vec3 vup,
    float vfov, 
    float aspect_ratio 
) {
    float theta = degrees_to_radians( vfov );
    float h = tan( theta / 2.0f );
    float viewport_height = 2.0f * h;
    float viewport_width = viewport_height * aspect_ratio;

    vec3 w = unit_vector( lookfrom - lookat );
    vec3 u = unit_vector( cross( vup, w ) );
    vec3 v = cross( w, u );

    m_origin = lookfrom;
    m_horizontal = viewport_width * u;
    m_vertical = viewport_height * v;
    m_lower_left_corner = m_origin - m_horizontal / 2 - m_vertical / 2 - w;
}

ray camera::get_ray( float s, float t ) const {
    return ray( m_origin, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin );
}