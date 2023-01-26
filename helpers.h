#ifndef HELPERS_H
#define HELPERS_H

#include <cmath>
#include <memory>
#include <limits>
#include <random>

// usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi = M_PI;

// utility functions
inline float degrees_to_radians( float degrees ) {
    return degrees * pi / 180.0f;
}

inline float random_float() {
    static std::uniform_real_distribution< float > distribution( 0.0f, 1.0f );
    static std::mt19937 generator;
    return distribution( generator );
}

inline float random_float( float min, float max ) {
    return min + random_float() * ( max - min );
}

// common headers
#include "ray.h"
#include "vec3.h"

#endif