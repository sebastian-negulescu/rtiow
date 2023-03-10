#include "vec3.h"

#include <cmath>

vec3::vec3() {}
vec3::vec3( float value ) {
    m_values[0] = value;
    m_values[1] = value;
    m_values[2] = value;
}
vec3::vec3( float value_0, float value_1, float value_2 ) {
    m_values[0] = value_0;
    m_values[1] = value_1;
    m_values[2] = value_2;
}

float vec3::x() { return m_values[0]; }
float vec3::y() { return m_values[1]; }
float vec3::z() { return m_values[2]; }

float vec3::r() { return m_values[0]; }
float vec3::g() { return m_values[1]; }
float vec3::b() { return m_values[2]; }

vec3 vec3::operator-() const { 
    return vec3( -1.0f * m_values[0], -1.0f * m_values[1], -1.0f * m_values[2] );
}

float vec3::operator[]( int index ) const { return m_values[index]; }
float & vec3::operator[]( int index ) { return m_values[index]; }

vec3 & vec3::operator+=( const vec3 & vec ) {
    m_values[0] += vec.m_values[0];
    m_values[1] += vec.m_values[1];
    m_values[2] += vec.m_values[2];
    return * this;
}
vec3 & vec3::operator-=( const vec3 & amount ) {
    return * this += -amount;
}

vec3 & vec3::operator*=( const float amount ) {
    m_values[0] *= amount;
    m_values[1] *= amount;
    m_values[2] *= amount;
    return * this;
}
vec3 & vec3::operator/=( const float amount ) {
    const float inverse_amount = 1 / amount;
    return * this *= amount;
}

float vec3::length() const {
    return std::sqrt(length_squared());
}

float vec3::length_squared() const {
    return (m_values[0] * m_values[0] + m_values[1] * m_values[1] + m_values[2] * m_values[2]);
}

bool vec3::near_zero() const {
    float epsilon = 0.00000001;
    return ( fabs( m_values[0] ) < epsilon ) && ( fabs( m_values[1] ) < epsilon ) && ( fabs( m_values[2] ) < epsilon );
}

vec3 random_in_unit_sphere() {
    while ( true ) {
        vec3 random_vec3 = vec3::random( -1.0f, 1.0f );
        if ( random_vec3.length_squared() < 1.0f ) {
            return random_vec3;
        }
    }
}

vec3 random_unit_vector() {
    return unit_vector( random_in_unit_sphere() );
}

vec3 random_in_hemisphere( const vec3 & normal ) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if ( dot( normal, in_unit_sphere )  > 0.0f ) {
        return in_unit_sphere;
    }
    return -in_unit_sphere;
}

vec3 random_in_unit_disk() {
    while ( true ) {
        vec3 random_vec3 = vec3( random_float( -1.0f, 1.0f ), random_float( -1.0f, 1.0f ), 0.0f );
        if ( random_vec3.length_squared() < 1.0f ) {
            return random_vec3;
        }
    }
}

vec3 reflect( const vec3 & v, const vec3 & n ) {
    return v - 2 * dot( v, n ) * n;
}

vec3 refract( const vec3 & uv, const vec3 & n, float etai_over_etat ) {
    float cos_theta = fmin( dot( -uv, n ), 1.0f );
    vec3 r_out_perp = etai_over_etat * ( uv + cos_theta * n );
    vec3 r_out_parallel = -sqrt( fabs( 1.0f - r_out_perp.length_squared() ) ) * n;
    return r_out_perp + r_out_parallel;
}