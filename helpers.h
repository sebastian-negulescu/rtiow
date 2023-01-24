#ifndef HELPERS_H
#define HELPERS_H

#include <cmath>
#include <memory>
#include <limits>

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

// common headers
#include "ray.h"
#include "vec3.h"

#endif