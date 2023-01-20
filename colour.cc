#include "colour.h"

void write_colour( std::ostream & out, colour pixel_colour ) {
    out << static_cast<int>( 255.999 * pixel_colour.r() ) << ' '
        << static_cast<int>( 255.999 * pixel_colour.g() ) << ' '
        << static_cast<int>( 255.999 * pixel_colour.b() );
}