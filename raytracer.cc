#include <iostream>

int main() {
    const unsigned int image_width = 256;
    const unsigned int image_height = 256;

    std::cout << "P3" << std::endl << image_width << ' ' << image_height << std::endl << "255" << std::endl;

    for ( unsigned int j = 0; j < image_height; ++j ) {
        for ( unsigned int i = 0; i < image_width; ++i ) {
            float r = float( i ) / ( image_width - 1 );
            float g = float( image_height - 1 - j ) / ( image_height - 1 );
            float b = 0.25f;

            unsigned int ir = static_cast<unsigned int>( 255.999f * r );
            unsigned int ig = static_cast<unsigned int>( 255.999f * g ); 
            unsigned int ib = static_cast<unsigned int>( 255.999f * b );

            std::cout << ir << ' ' << ig << ' ' << ib << std::endl;
            std::cerr << j + 1 << " lines scanned out of " << image_height << std::endl;
        }
    }

    std::cerr << "finished scanning" << std::endl;
}