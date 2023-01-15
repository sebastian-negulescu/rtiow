#include "vec3.h"

vec3::vec3() : m_values{ 0.0f, 0.0f, 0.0f } {}
vec3::vec3( float value ) : m_values{ value, value, value } {}
vec3::vec3( float value_0, float value_1, float value_2 ) : m_values{ value_0, value_1, value_2 } {}