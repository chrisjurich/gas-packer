cmake_minimum_required(VERSION 3.0)
project(ideal_gas_simulation)

include_directories(src/)

set(CMAKE_CXX_STANDARD 17)

set( src_files
        src/Config.h
        src/GasAtom.cpp
        src/GasBox.cpp
        src/gb_utils.cpp
        src/GBConfig.cpp
        src/LJPotential.cpp
        src/Metropolis.cpp
        )

add_library( ideal_gas_engine ${src_files})

#target_link_libraries( ideal_gas_engine )


add_executable( ideal_gas_simulator src/main.cpp)

target_link_libraries (ideal_gas_simulator ideal_gas_engine)


#add_subdirectory(pybind11/)
find_package(pybind11)

pybind11_add_module( gas_packer ${src_files} src/bindings.cpp )

target_link_libraries( gas_packer PUBLIC ideal_gas_engine)

