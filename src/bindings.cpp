#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <memory>

#include <gb_utils.h>
#include <GasAtom.h>
#include <GasBox.h>

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




namespace py = pybind11;

PYBIND11_MODULE(gas_packer, m) {

    py::register_exception<BadValue>(m,"BadValueException");

    py::class_<Dimensions,std::shared_ptr<Dimensions>>(m,"Dimensions")
        .def(py::init<double,double,double,double,double,double>())
        .def_readwrite("x_min", &Dimensions::x_min)
        .def_readwrite("x_max", &Dimensions::x_max)
        .def_readwrite("y_min", &Dimensions::y_min)
        .def_readwrite("y_max", &Dimensions::y_max)
        .def_readwrite("z_min", &Dimensions::z_min)
        .def_readwrite("z_max", &Dimensions::z_max)
        ;

    py::class_<BoxSnapShot,std::shared_ptr<BoxSnapShot>>(m,"BoxSnapShot")
        .def_readwrite("accepted_moves",&BoxSnapShot::accepted_moves)
        .def_readwrite("rejected_moves",&BoxSnapShot::rejected_moves)
        .def_readwrite("temperature",&BoxSnapShot::temperature)
        .def_readwrite("min_distance",&BoxSnapShot::min_distance)
        .def_readwrite("max_distance",&BoxSnapShot::max_distance)
        ;

    py::class_<Position,std::shared_ptr<Position>>(m,"Position")
        // ctors 
        .def(py::init<int,int,int>())
        // methods 
        .def_readwrite("x",&Position::x)
        .def_readwrite("y",&Position::y)
        .def_readwrite("z",&Position::z)
        .def("to_string",&Position::to_string) 
        .def("apply_bounds",&Position::apply_bounds) 
        // operators 
        .def(py::self += py::self)
        .def(py::self + py::self)
        ;


    py::class_<GasAtom,std::shared_ptr<GasAtom>>(m,"GasAtom")
        //ctors 
        .def(py::init<double,double,double,const Dimensions&, unsigned int>())
        // methods 
        .def("distance",[](GasAtom const& ga, const Position & p) -> double { return ga.distance(p);})
        .def("distance",[](GasAtom const& ga, const GasAtom & other) -> double { return ga.distance(other);})
        .def("proposed_move",&GasAtom::proposed_move)
        .def("id",&GasAtom::id)
        .def("positions",&GasAtom::positions)
        .def("get_position",&GasAtom::get_position)
        // operators 
        .def(py::self += py::self)
        .def(py::self += py::self) 
        ;

//    friend std::ostream& operator<<(std::ostream& os, const GasAtom& GA)
//    {
//        os<<"atom id: "<<GA.atom_id<<" location ("<<GA.curr_pos.x<<","<<GA.curr_pos.y<<","<<GA.curr_pos.z<<")\n";
//        return os;
//    }
//
//};
    py::class_<GasBox,std::shared_ptr<GasBox>>(m,"GasBox")
        //ctors 
        .def(py::init<int,int,double,double,double,double,double,double,double,std::string>())
        .def(py::init<GasBoxConfig const &>())
        // methods    
        .def("initialize",&GasBox::initialize)
        .def("caluclate_distances",&GasBox::caluclate_distances)
        .def("simulate",&GasBox::simulate)
        .def("to_csv",&GasBox::to_csv)
        ;

}
