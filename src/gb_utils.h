#ifndef __GB_UTILS_H__
#define __GB_UTILS_H__
#include <utility>
#include <functional>

namespace std {
    template <typename T1,typename T2> 
    struct hash<pair<T1,T2>>  {
        size_t
        operator()(const pair<T1,T2>& input_pair)const {
            return hash<T1>()(input_pair.first)^hash<T2>()(input_pair.second);
        }
    };
}



struct Dimensions {

double x_min, x_max, y_min, y_max, z_min, z_max;

Dimensions(
        double x_min=0.,
        double x_max=0.,
        double y_min=0.,
        double y_max=0.,
        double z_min=0.,
        double z_max=0.
        ) : x_min(x_min),
            x_max(x_max),
            y_min(y_min),
            y_max(y_max),
            z_min(z_min),
            z_max(z_max) {}


};

#endif // __GB_UTILS_H__
