#include "material.h"
#include "hittable.h"

lambertian::lambertian( const colour & a ) : m_albedo( a ) {}

bool lambertian::scatter( const ray & r_in, const hit_record & record, colour & attenuation, ray & scattered ) const {
    vec3 scatter_direction = record.normal + random_unit_vector();
    if ( scatter_direction.near_zero() ) {
        scatter_direction = record.normal;
    }

    scattered = ray( record.point, scatter_direction );
    attenuation = m_albedo;
    return true;
}

metal::metal( const colour & a ) : m_albedo( a ) {}

bool metal::scatter( const ray & r_in, const hit_record & record, colour & attenuation, ray & scattered ) const {
    vec3 reflected = reflect( unit_vector(r_in.direction()), record.normal );
    scattered = ray( record.point, reflected );
    attenuation = m_albedo;
    return dot( scattered.direction(), record.normal ) > 0;
}
