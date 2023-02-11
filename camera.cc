#include "camera.h"

camera::camera( 
    point3 lookfrom,
    point3 lookat,
    vec3 vup,
    float vfov, 
    float aspect_ratio,
    float aperture,
    float focus_dist
) {
    float theta = degrees_to_radians( vfov );
    float h = tan( theta / 2.0f );
    float viewport_height = 2.0f * h;
    float viewport_width = viewport_height * aspect_ratio;

    w = unit_vector( lookfrom - lookat );
    u = unit_vector( cross( vup, w ) );
    v = cross( w, u );

    m_origin = lookfrom;
    m_horizontal = focus_dist * viewport_width * u;
    m_vertical = focus_dist * viewport_height * v;
    m_lower_left_corner = m_origin - m_horizontal / 2 - m_vertical / 2 - focus_dist * w;

    m_lens_radius = aperture / 2;
}

ray camera::get_ray( float s, float t ) const {
    vec3 rd = m_lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();
    return ray( m_origin + offset, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin - offset );
}