#ifndef __GB_UTILS_H__
#define __GB_UTILS_H__

#include <utility>
#include <functional>
#include <cmath>
#include <stdexcept>
#include <string>

class BadValue : public std::runtime_error {
    public: 
        BadValue(const std::string& msg) : std::runtime_error(msg) {}

};
// constants
static const double epsilon(1.);
static const double r_m(1.);
static const double e(2.7182818284590452353602874);
static const double R(8.3144621);
static const double vdw_radius(0.01);

namespace std {
    template <typename T1,typename T2> 
    struct hash<pair<T1,T2>>  {
        size_t
        operator()(const pair<T1,T2>& input_pair)const {
            return hash<T1>()(input_pair.first)^hash<T2>()(input_pair.second);
        }
    };
}

double
rms_velocity(double, double ,double );

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

struct BoxSnapShot {
    
    int accepted_moves;
    int rejected_moves;
    double temperature;
    double min_distance;
    double max_distance;
    
    BoxSnapShot(
            int accepted_moves,
            int rejected_moves,
            double temperature,
            double min_distance,
            double max_distance
            ) : accepted_moves(accepted_moves),
                rejected_moves(rejected_moves),
                temperature(temperature),
                min_distance(min_distance),
                max_distance(max_distance) {

                }
    BoxSnapShot() : 
        accepted_moves(0),
        rejected_moves(0),
        temperature(-1.),
        min_distance(-1.),
        max_distance(-1.) {}


};
#endif // __GB_UTILS_H__
