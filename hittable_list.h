#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public hittable {
    std::vector< std::shared_ptr< hittable > > m_objects; 

  public:
    hittable_list();
    hittable_list( std::shared_ptr< hittable > object );

    void clear();
    void add( std::shared_ptr< hittable > object );

    bool hit( const ray & r, float t_min, float t_max, hit_record & record ) const override;
};

#endif