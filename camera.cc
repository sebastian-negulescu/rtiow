#include "camera.h"

camera::camera( float vfov, float aspect_ratio ) {
    float theta = degrees_to_radians( vfov );
    float h = tan( theta / 2.0f );
    float viewport_height = 2.0f * h;
    float viewport_width = viewport_height * aspect_ratio;

    float focal_length = 1.0f;

    m_origin = point3( 0.0f );
    m_horizontal = vec3( viewport_width, 0.0f, 0.0f );
    m_vertical = vec3( 0.0f, viewport_height, 0.0f );
    m_lower_left_corner = m_origin - m_horizontal / 2 - m_vertical / 2 - vec3( 0.0f, 0.0f, focal_length );
}

ray camera::get_ray( float u, float v ) const {
    return ray( m_origin, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin );
}