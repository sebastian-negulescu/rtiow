#ifndef VEC3_H
#define VEC3_H

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

    vec3 & operator+=( const float amount );
    vec3 & operator-=( const float amount );

    vec3 & operator*=( const float amount );
    vec3 & operator/=( const float amount );

    float length() const;
    float length_squared() const;

    friend inline std::ostream & operator<<( std::ostream & out, const vec3 & v );

    friend inline vec3 operator+( const vec3 & u, const vec3 & v ) ;
    friend inline vec3 operator-( const vec3 & u, const vec3 & v );

    friend inline vec3 operator*( const vec3 & u, const vec3 & v );
    friend inline vec3 operator*( float t, const vec3 & v );
    friend inline vec3 operator*( const vec3 & v, float t );
    friend inline vec3 operator/( const vec3 & v, float t );

    friend inline vec3 dot( const vec3 & u, const vec3 & v );
    friend inline vec3 cross( const vec3 & u, const vec3 & v );
    friend inline vec3 unit_vector( const vec3 & v );
};

using point3 = vec3;
using colour = vec3;

#endif