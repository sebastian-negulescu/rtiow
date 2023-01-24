#include "hittable_list.h"

hittable_list::hittable_list() {}
hittable_list::hittable_list( std::shared_ptr< hittable > object ) { add( object ); }

void hittable_list::clear() { m_objects.clear(); }
void hittable_list::add( std::shared_ptr< hittable > object ) { m_objects.push_back( object ); }

bool hittable_list::hit( const ray & r, float t_min, float t_max, hit_record & record ) const {
    hit_record temp_record;
    bool hit_anything = false;
    float min_distance = t_max;

    for ( const std::shared_ptr< hittable > object : m_objects ) {
        if ( object->hit( r, t_min, t_max, temp_record ) ) {
            hit_anything = true;
            min_distance = temp_record.t;
            record = temp_record;
        }
    }
}