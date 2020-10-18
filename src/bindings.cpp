// C++ library includes
#include <memory>
// pybind includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
// gas packer includes
#include <gb_utils.h>
#include <GasAtom.h>
#include <GasBox.h>
#include <GBConfig.h>
#include <LJPotential.h>
#include <Metropolis.h>

namespace py = pybind11;

PYBIND11_MODULE(gas_packer, m) {

//////////////////////////////////////////////////////////////////////////////////
////        gb_utils.h
//////////////////////////////////////////////////////////////////////////////////
    py::register_exception<BadValue>(m,"BadValueException");

    m.def("rms_velocity",rms_velocity);

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

//////////////////////////////////////////////////////////////////////////////////
////        GasAtom.h
//////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////
////        GBConfig.h
//////////////////////////////////////////////////////////////////////////////////

    py::class_<GasBoxConfig,std::shared_ptr<GasBoxConfig>>(m,"GasBoxConfig")
        .def(py::init<>())  
        .def_readwrite("num_atoms",&GasBoxConfig::num_atoms)
        .def_readwrite("rng_seed",&GasBoxConfig::rng_seed)
        .def_readwrite("num_moves",&GasBoxConfig::num_moves)
        .def_readwrite("outfile",&GasBoxConfig::outfile)
        .def_readwrite("x_min",&GasBoxConfig::x_min)
        .def_readwrite("x_max",&GasBoxConfig::x_max)
        .def_readwrite("y_min",&GasBoxConfig::y_min)
        .def_readwrite("y_max",&GasBoxConfig::y_max)
        .def_readwrite("z_min",&GasBoxConfig::z_min)
        .def_readwrite("z_max",&GasBoxConfig::z_max)
        .def_readwrite("move_dist",&GasBoxConfig::move_dist)
        ;
    
    py::class_<GasBox,std::shared_ptr<GasBox>>(m,"GasBox")
        //ctors 
        .def(py::init<>())
        .def(py::init<int,int,double,double,double,double,double,double,double,std::string>())
        // methods
        .def("initialize",&GasBox::initialize)
        .def("caluclate_distances",&GasBox::caluclate_distances)
        .def("simulate",&GasBox::simulate)
        .def("to_csv",&GasBox::to_csv)
        .def("moves",&GasBox::moves)
        ;

//////////////////////////////////////////////////////////////////////////////////
////        LJPotential.h
//////////////////////////////////////////////////////////////////////////////////

    py::class_<LennardJonesPotential,std::shared_ptr<LennardJonesPotential>>(m,"LennardJonesPotential")
        // ctors
        .def(py::init<const double&,const double&>())
        // methods
        .def("energy", [] (LennardJonesPotential& lj, const double e) -> double {return lj.energy(e);})
        .def("energy", [] (LennardJonesPotential& lj, const GasAtom& g1, const GasAtom& g2) -> double { return lj.energy(g1, g2); })
        ;

//////////////////////////////////////////////////////////////////////////////////
////        Metropolis.h
//////////////////////////////////////////////////////////////////////////////////

    py::class_<MetropolisSelector,std::shared_ptr<MetropolisSelector>>(m, "MetropolisSelector")
        // ctors
        .def(py::init<>())
        //methods
        .def("accept", &MetropolisSelector::accept_move)
        ;

}
