#include "heart.h"

#include <cmath>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_const.h>

heart::heart() : m_center( 0.0f ), m_radius( 0.0f ) {}
heart::heart( point3 center, float radius, shared_ptr< material > material )
    : m_center( center ), m_radius( radius ), m_material_ptr( material ) {}

bool heart::hit( const ray & r, float t_min, float t_max, hit_record & record ) const {
    point3 origin = r.origin();
    float ox = origin.x();
    float oz = origin.y();
    float oy = -origin.z();

    double ox_squared = pow(ox, 2);
    double oy_squared = pow(oy, 2);
    double oz_squared = pow(oz, 2);

    vec3 direction = r.direction();
    float dx = direction.x();
    float dz = direction.y();
    float dy = -direction.z();

    double dx_squared = pow(dx, 2);
    double dy_squared = pow(dy, 2);
    double dz_squared = pow(dz, 2);

    double alpha = pow(ox, 2) + (9 / 4) * pow(oy, 2) + pow(oz, 2) - 1;
    double beta = 2 * ox * dx + (9 / 2) * oy * dy + 2 * oz * dz;
    double gamma = pow(dx, 2) + (9 / 4) * pow(dy, 2) + pow(dz, 2);

    double beta_squared = pow(beta, 2);

    double coef_0 = pow(alpha, 3)
         - ox_squared * pow(oz, 3)
         - (9 / 200) * oy_squared * pow(oz, 3);
    double coef_1 = 3 * pow(alpha, 2) * beta
         - (3 * ox_squared * oz_squared * dz + 2 * ox * dx * pow(oz, 3))
         - (9 / 200) * (3 * oy_squared * oz_squared * dz + 2 * oy * dy * pow(oz, 3));
    double coef_2 = 3 * alpha * (alpha * gamma + beta_squared)
         - (3 * ox_squared * oz * dz_squared + 6 * ox * dx * oz_squared * dz + dx_squared * pow(oz, 3))
         - (9 / 200) * (3 * oy_squared * oz * dz_squared + 6 * oy * dy * oz_squared * dz + dy_squared * pow(oz, 3));
    double coef_3 = beta * (6 * alpha * gamma + beta_squared)
         - (ox_squared * pow(dz, 3) + 6 * ox * dx * oz * dz_squared + 3 * dx_squared * oz_squared * dz)
         - (9 / 200) * (oy_squared * pow(dz, 3) + 6 * oy * dy * oz * dz_squared + 3 * dy_squared * oz_squared * dz);
    double coef_4 = 3 * gamma * (alpha * gamma + beta_squared)
         - (2 * ox * dx * pow(dz, 3) + 3 * dx_squared * oz * dz_squared)
         - (9 / 200) * (2 * oy * dy * pow(dz, 3) + 3 * dy_squared * oz * dz_squared);
    double coef_5 = 3 * beta * pow(gamma, 2)
         - dx_squared * pow(dz, 3)
         - (9 / 200) * dy_squared * pow(dz, 3);
    double coef_6 = pow(gamma, 3);

    double coefficients[7] = {coef_0, coef_1, coef_2, coef_3, coef_4, coef_5, coef_6};
    double solutions[12];
    gsl_poly_complex_workspace * gpcw = gsl_poly_complex_workspace_alloc(7);

    int error = gsl_poly_complex_solve(coefficients, 7, gpcw, solutions);

    gsl_poly_complex_workspace_free(gpcw);

    if ( error != 0 ) {
        std::cerr << "error" <<std::endl;
        return false;
    }
    
    bool found_root = false;
    for ( int index = 0; index < 6; ++index ) {
        if ( solutions[index + 1] == 0.0 ) { // real root
            if ( solutions[index] > t_min ) {
                record.t = solutions[index];
                found_root = true;
                break;
            }
        }
    }
    if ( !found_root ) {
        return false;
    }

    // std::cerr << "here" << std::endl;

    record.point = r.at( record.t );
    vec3 outward_normal = unit_vector( record.point - m_center ); // treated as a sphere
    record.set_face_normal( r, outward_normal );
    record.material_ptr = m_material_ptr;

    return true;
}