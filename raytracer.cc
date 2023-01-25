#include "helpers.h"

#include "colour.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

float hit_sphere( const point3 & center, float radius, const ray & r ) {
    vec3 oc = r.origin() - center;
    float a = r.direction().length_squared();
    float half_b = dot( oc, r.direction() );
    float c = dot( oc, oc ) - radius * radius;

    float descriminant = half_b * half_b - a * c;
    if ( descriminant < 0.0f ) {
        return -1.0f;
    } else {
        return ( -half_b - sqrt( descriminant ) ) / a;
    }
}

colour ray_colour( const ray & r, const hittable & world) {
    hit_record record;
    if ( world.hit( r, 0.0f, infinity, record ) ) {
        return 0.5f * ( record.normal + colour( 1.0f ) );
    }

    vec3 unit_direction = unit_vector( r.direction() );
    float t = 0.5f * ( unit_direction.y() + 1.0f );
    return ( 1.0f - t ) * colour( 1.0f ) + t * colour( 0.5f, 0.7f, 1.0f );
}

int main() {

    // image dimensions

    const float aspect_ratio = 16.0f / 9.0f;
    const unsigned int image_width = 400;
    const unsigned int image_height = static_cast< int >( image_width / aspect_ratio );

    // world

    hittable_list world;
    world.add( make_shared< sphere >( point3( 0.0f, 0.0f, -1.0f ), 0.5f ) );
    world.add( make_shared< sphere >( point3( 0.0f, -100.5f, -1.0f ), 100.0f ) );

    // camera

    float viewport_height = 2.0f;
    float viewport_width = viewport_height * aspect_ratio;
    float focal_length = 1.0f;

    point3 origin( 0.0f );
    vec3 horizontal( viewport_width, 0.0f, 0.0f );
    vec3 vertical( 0.0f, viewport_height, 0.0f );
    point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3( 0.0f, 0.0f, focal_length );

    std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;

    for ( unsigned int j = 0; j < image_height; ++j ) {
        for ( unsigned int i = 0; i < image_width; ++i ) {
            float u = float( i ) / ( image_width - 1 );
            float v = float( image_height - 1 - j ) / ( image_height - 1 );

            ray r( origin, lower_left_corner + u * horizontal + v * vertical - origin );
            colour pixel_colour = ray_colour( r, world );
            write_colour( std::cout, pixel_colour );
            
        }
        std::cerr << j + 1 << " lines scanned out of " << image_height << std::endl;
    }

    std::cerr << "finished scanning" << std::endl;
}