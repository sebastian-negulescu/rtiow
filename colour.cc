#include "colour.h"

void write_colour( std::ostream & out, colour pixel_colour, unsigned int samples_per_pixel ) {
    float r = pixel_colour.r();
    float g = pixel_colour.g();
    float b = pixel_colour.b();

    float scale = 1.0f / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    out << static_cast<int>( 256 * clamp( r, 0.0f, 0.999f ) ) << ' '
        << static_cast<int>( 256 * clamp( g, 0.0f, 0.999f ) ) << ' '
        << static_cast<int>( 256 * clamp( b, 0.0f, 0.999f ) ) << std::endl;
}