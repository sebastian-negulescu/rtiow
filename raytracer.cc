#include "colour.h"
#include "vec3.h"

#include <iostream>

int main() {
    const unsigned int image_width = 256;
    const unsigned int image_height = 256;

    std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;

    for ( unsigned int j = 0; j < image_height; ++j ) {
        for ( unsigned int i = 0; i < image_width; ++i ) {

            colour pixel_colour( 
                float( i ) / ( image_width - 1 ), 
                float( image_height - 1 - j ) / ( image_height - 1 ), 
                0.25f 
            );

            write_colour( std::cout, pixel_colour );
            
            std::cerr << j + 1 << " lines scanned out of " << image_height << std::endl;
        }
    }

    std::cerr << "finished scanning" << std::endl;
}