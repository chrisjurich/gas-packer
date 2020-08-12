#include <pybind11/pybind11.h>
#include <memory>

#include <gb_utils.h>

//static const double epsilon(1.);
//static const double r_m(1.);
//static const double e(2.7182818284590452353602874);
//static const double R(8.3144621);
//static const double vdw_radius(0.01);
//
//namespace std {
//    template <typename T1,typename T2> 
//    struct hash<pair<T1,T2>>  {
//        size_t
//        operator()(const pair<T1,T2>& input_pair)const {
//            return hash<T1>()(input_pair.first)^hash<T2>()(input_pair.second);
//        }
//    };
//}
//
//double
//rms_velocity(double, double ,double );
//

//
//struct BoxSnapShot {
//    
//    int accepted_moves;
//    int rejected_moves;
//    double temperature;
//    double min_distance;
//    double max_distance;
//    
//    BoxSnapShot(
//            int accepted_moves,
//            int rejected_moves,
//            double temperature,
//            double min_distance,
//            double max_distance
//            ) : accepted_moves(accepted_moves),
//                rejected_moves(rejected_moves),
//                temperature(temperature),
//                min_distance(min_distance),
//                max_distance(max_distance) {
//
//                }
//    BoxSnapShot() : 
//        accepted_moves(0),
//        rejected_moves(0),
//        temperature(-1.),
//        min_distance(-1.),
//        max_distance(-1.) {}
//
//
//};
//#

int
add(int one, int two) {
    return one + two;
}

namespace py = pybind11;

PYBIND11_MODULE(gas_packer, m) {

    py::register_exception<BadValue>(m,"BadValueException");

    py::class_<Dimensions,std::shared_ptr<Dimensions>>(m,"Dimensions")
        .def_readwrite("x_min", &Dimensions::x_min)
        .def_readwrite("x_max", &Dimensions::x_max)
        .def_readwrite("y_min", &Dimensions::y_min)
        .def_readwrite("y_max", &Dimensions::y_max)
        .def_readwrite("z_min", &Dimensions::z_min)
        .def_readwrite("z_max", &Dimensions::z_max)
        ;
}
