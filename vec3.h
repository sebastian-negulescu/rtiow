#ifndef VEC3_H
#define VEC3_H

#include "helpers.h"

#include <iostream>

class vec3 {

  public:
    float m_values[3] = { 0.0f, 0.0f, 0.0f };

    vec3();
    vec3( float value );
    vec3( float value_0, float value_1, float value_2 );

    float x();
    float y();
    float z();   

    float r();
    float g();
    float b();

    vec3 operator-() const;

    float operator[]( int index ) const;
    float & operator[]( int index );

    vec3 & operator+=( const vec3 & amount );
    vec3 & operator-=( const vec3 & amount );

    vec3 & operator*=( const float amount );
    vec3 & operator/=( const float amount );

    float length() const;
    float length_squared() const;

    inline static vec3 random() {
        return vec3( random_float(), random_float(), random_float() );
    }

    inline static vec3 random( float min, float max ) {
        return vec3( random_float( min, max ), random_float( min, max ), random_float( min, max ) );
    }

    vec3 random_in_unit_sphere();

    friend inline std::ostream & operator<<( std::ostream & out, const vec3 & v ) {
        return out << v.m_values[0] << ' ' << v.m_values[1] << ' ' << v.m_values[2];
    } 

    friend inline vec3 operator+( const vec3 & u, const vec3 & v ) {
        return vec3( 
            u.m_values[0] + v.m_values[0], 
            u.m_values[1] + v.m_values[1], 
            u.m_values[2] + v.m_values[2] 
        );
    }
    friend inline vec3 operator-( const vec3 & u, const vec3 & v ) {
        return vec3( 
            u.m_values[0] - v.m_values[0], 
            u.m_values[1] - v.m_values[1], 
            u.m_values[2] - v.m_values[2] 
        );
    }

    friend inline vec3 operator*( const vec3 & u, const vec3 & v ) {
        return vec3( 
            u.m_values[0] * v.m_values[0], 
            u.m_values[1] * v.m_values[1], 
            u.m_values[2] * v.m_values[2] 
        );
    }
    friend inline vec3 operator*( float t, const vec3 & v ) {
        return vec3( t * v.m_values[0], t * v.m_values[1], t * v.m_values[2] );
    }
    friend inline vec3 operator*( const vec3 & v, float t ) {
        return t * v;
    }
    friend inline vec3 operator/( const vec3 & v, float t ) {
        return ( 1 / t ) * v;
    }

    friend inline float dot( const vec3 & u, const vec3 & v ) {
        return u.m_values[0] * v.m_values[0]
             + u.m_values[1] * v.m_values[1]
             + u.m_values[2] * v.m_values[2];
    }
    friend inline vec3 cross( const vec3 & u, const vec3 & v ) {
        return vec3( u.m_values[1] * v.m_values[2] - u.m_values[2] * v.m_values[1],
                     u.m_values[2] * v.m_values[0] - u.m_values[0] * v.m_values[2],
                     u.m_values[0] * v.m_values[1] - u.m_values[1] * v.m_values[0] );
    }
    friend inline vec3 unit_vector( const vec3 & v ) {
        return v / v.length();
    }
};

using point3 = vec3;
using colour = vec3;

#endif