#include "helpers.h"

#include "colour.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

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

colour ray_colour( const ray & r, const hittable & world, unsigned int depth ) {
    hit_record record;

    if ( depth <= 0 ) {
        return colour( 0.0f );
    }

    if ( world.hit( r, 0.001f, infinity, record ) ) {
        // return 0.5f * ( record.normal + colour( 1.0f ) );
        // point3 target = record.point + random_in_hemisphere( record.normal ); // record.normal + random_unit_vector();
        // return 0.5f * ray_colour( ray( record.point, target - record.point ), world, depth - 1 );

        ray scattered;
        colour attenuation;
        if ( record.material_ptr->scatter( r, record, attenuation, scattered ) ) {
            return attenuation * ray_colour( scattered, world, depth - 1 );
        }
        return colour( 0.0f );
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
    const unsigned int samples_per_pixel = 100;
    const unsigned int max_depth = 50;

    // world

    hittable_list world;

    auto material_ground = make_shared< lambertian >( colour( 0.8f, 0.8f, 0.0f ) );
    auto material_center = make_shared< dielectric >( 1.5f );// make_shared< lambertian >( colour( 0.7f, 0.3f, 0.3f ) );
    auto material_left = make_shared< metal >( colour( 0.8f, 0.8f, 0.8f ), 0.3f );
    auto material_right = make_shared< metal >( colour ( 0.8f, 0.6f, 0.2f ), 1.0f );

    world.add( make_shared< sphere >( point3( 0.0f, -100.5f, -1.0f ), 100.0f, material_ground ) );
    world.add( make_shared< sphere >( point3( 0.0f, 0.0f, -1.0f ), 0.5f, material_center ) );
    world.add( make_shared< sphere >( point3( -1.0f, 0.0f, -1.0f ), 0.5f, material_left ) );
    world.add( make_shared< sphere >( point3( 1.0f, 0.0f, -1.0f ), 0.5f, material_right ) );

    // camera

    camera cam;

    std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;

    for ( unsigned int j = 0; j < image_height; ++j ) {
        for ( unsigned int i = 0; i < image_width; ++i ) {
            float u = float( i ) / ( image_width - 1 );
            float v = float( image_height - 1 - j ) / ( image_height - 1 );

            colour pixel_colour( 0.0f );
            for ( int s = 0; s < samples_per_pixel; ++s ) {
                float u = ( i + random_float() ) / ( image_width - 1 );
                float v = ( image_height - 1 - j + random_float() ) / ( image_height - 1 );
                ray r = cam.get_ray( u, v );
                pixel_colour += ray_colour( r, world, max_depth );
            }
            write_colour( std::cout, pixel_colour, samples_per_pixel );
            
        }
        std::cerr << j + 1 << " lines scanned out of " << image_height << std::endl;
    }

    std::cerr << "finished scanning" << std::endl;
}