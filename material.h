#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"

struct hit_record;

class material {
  public:
    virtual bool scatter( const ray & r_in, const hit_record & record, colour & attenuation, ray & scattered ) const = 0;
};

class lambertian : public material {
    colour m_albedo;

  public:
    lambertian( const colour & a );

    bool scatter( const ray & r_in, const hit_record & record, colour & attenuation, ray & scattered ) const override;
};

class metal : public material {
    colour m_albedo;
    float m_fuzz;

  public:
    metal( const colour & a, float fuzz );

    bool scatter( const ray & r_in, const hit_record & record, colour & attenuation, ray & scattered ) const override;
};

class dielectric : public material {
    float m_ir;
    static float reflectance( float cosine, float ref_idx );

  public:
    dielectric( float index_of_refraction );

    bool scatter( const ray & r_in, const hit_record & record, colour & attenuation, ray & scattered ) const override;
};

#endif