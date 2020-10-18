cmake_minimum_required(VERSION 3.0)
project(CJ-GAS-PACKER)
set(CMAKE_CXX_STANDARD 17)

option(BINDINGS "Toggle for bindings generation" ON)
option(CPP "Toggle for CPP generation" ON)

if(BINDINGS)
    find_package (Python COMPONENTS Interpreter Development)
else()
    message(">>>NOTE:")
    message(">>>BINDINGS option is set to OFF. Python bindings will NOT be made")
    message(">>>To change, delete CMakeCache.txt file and run the command cmake [-G Ninja] .")
endif()
if(NOT CPP)
    message(">>>NOTE:")
    message(">>>CPP option is set to OFF. The executable \"CJ-GAS-PACKER\" will NOT be made")
    message(">>>To change, delete CMakeCache.txt file and run the command cmake [-G Ninja] .")
endif()
# all files are withing src/
include_directories(src/)
include_directories(src/external/)
if(BINDINGS)
    add_subdirectory(pybind11/)
    # need to set the pybind11 directory
    set(pybind11_DIR pybind11/)
endif()

if(CPP OR BINDINGS)
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
endif()

if(CPP)
    add_executable( CJ-GAS-PACKER src/main.cpp)
    target_link_libraries( CJ-GAS-PACKER gas_engine)
endif()
if(BINDINGS)
    # this is the python module
    pybind11_add_module( cj_gas_packer ${src_files} src/bindings.cpp )
    target_link_libraries( cj_gas_packer PUBLIC gas_engine)
endif()