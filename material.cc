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

metal::metal( const colour & a, float fuzz ) : m_albedo( a ), m_fuzz( fuzz ) {}

bool metal::scatter( const ray & r_in, const hit_record & record, colour & attenuation, ray & scattered ) const {
    vec3 reflected = reflect( unit_vector( r_in.direction() ), record.normal );
    scattered = ray( record.point, reflected + m_fuzz * random_in_unit_sphere() );
    attenuation = m_albedo;
    return dot( scattered.direction(), record.normal ) > 0;
}

float dielectric::reflectance( float cosine, float ref_idx ) {
    float r0 = ( 1 - ref_idx ) / ( 1 + ref_idx );
    r0 = r0 * r0;
    return r0 + ( 1 - r0 ) * pow( ( 1 - cosine ), 5 );
}

dielectric::dielectric( float index_of_refraction ) : m_ir( index_of_refraction ) {}

bool dielectric::scatter( const ray & r_in, const hit_record & record, colour & attenuation, ray & scattered ) const {
    attenuation = colour( 1.0f );    
    float refraction_ratio = record.front_face ? ( 1.0f / m_ir ) : m_ir;

    vec3 unit_direction = unit_vector( r_in.direction() );
    float cos_theta = fmin( dot( -unit_direction, record.normal ), 1.0f );
    float sin_theta = sqrt( 1.0f - cos_theta * cos_theta );
    
    bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
    vec3 direction;

    if ( cannot_refract || reflectance( cos_theta, refraction_ratio ) > random_float() ) {
        direction = reflect( unit_direction, record.normal );
    } else {
        direction = refract( unit_direction, record.normal, refraction_ratio );
    }

    scattered = ray( record.point, direction );
    return true;
}