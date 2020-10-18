cmake_minimum_required(VERSION 3.0)
project(CJ-GAS-PACKER)
set(CMAKE_CXX_STANDARD 17)

find_package (Python COMPONENTS Interpreter Development)

# all files are withing src/
include_directories(src/)
include_directories(src/external/)
add_subdirectory(pybind11/)
# need to set the pybind11 directory
set(pybind11_DIR pybind11/)

set( src_files
        src/GasAtom.cpp
        src/GasBox.cpp
        src/gb_utils.cpp
        src/GBConfig.cpp
        src/LJPotential.cpp
        src/Metropolis.cpp
        )
# this is the C++ executable
add_library( gas_engine ${src_files})
add_executable( CJ-GAS-PACKER src/main.cpp)
target_link_libraries( CJ-GAS-PACKER gas_engine)

# this is the python module
pybind11_add_module( cj_gas_packer ${src_files} src/bindings.cpp )
target_link_libraries( cj_gas_packer PUBLIC gas_engine)