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

vec3 & vec3::operator+=( const float amount ) {
    m_values[0] += amount;
    m_values[1] += amount;
    m_values[2] += amount;
    return * this;
}
vec3 & vec3::operator-=( const float amount ) {
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

std::ostream & operator<<( std::ostream & out, const vec3 & v ) {
    return out << v.m_values[0] << ' ' << v.m_values[1] << ' ' << v.m_values[2];
}

vec3 operator+( const vec3 & u, const vec3 & v ) {
    return vec3( u.m_values[0] + v.m_values[0], u.m_values[1] + v.m_values[1], u.m_values[2] + v.m_values[2] );
}

vec3 operator-( const vec3 & u, const vec3 & v ) {
    return vec3( u.m_values[0] - v.m_values[0], u.m_values[1] - v.m_values[1], u.m_values[2] - v.m_values[2] );
}

vec3 operator*( const vec3 & u, const vec3 & v ) {
    return vec3( u.m_values[0] * v.m_values[0], u.m_values[1] * v.m_values[1], u.m_values[2] * v.m_values[2] );
}

vec3 operator*( float t, const vec3 & v ) {
    return vec3( t * v.m_values[0], t * v.m_values[1], t * v.m_values[2] );
}

vec3 operator*( const vec3 & v, float t ) {
    return t * v;
}

vec3 operator/( const vec3 & v, float t ) {
    return ( 1 / t ) * v;
}

vec3 dot( const vec3 & u, const vec3 & v ) {
    return u.m_values[0] * v.m_values[0]
         + u.m_values[1] * v.m_values[1]
         + u.m_values[2] * v.m_values[2];
}

vec3 cross( const vec3 & u, const vec3 & v ) {
    return vec3( u.m_values[1] * v.m_values[2] - u.m_values[2] * v.m_values[1],
                 u.m_values[2] * v.m_values[0] - u.m_values[0] * v.m_values[2],
                 u.m_values[0] * v.m_values[1] - u.m_values[1] * v.m_values[0] );
}

vec3 unit_vector( const vec3 & v ) {
    return v / v.length();
}