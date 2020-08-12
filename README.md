# Gas Packer
This is a toy project that packs a set of gas molcules into a box.

## Install

There are two options for installation: native C++ code and python bindings

### Native C++
This project is built using C++17 as well as CMake and Ninja. It will compile with clang or gcc. The following command compiles the source code:


`$ cd build && cmake [-G Ninja] .. && [Ninja|Make]`


### Python Bindings
This project also supports python bindings with [pybind11](https://github.com/pybind/pybind11). This installation requires CMake, a working compiler and is only tested for python3. To install the bindings, use the following command:


`$ pip install . --user`


The module can then be imported with: 

`import gas_packer`


## Running Simulations

TODO

## Visuaalizing Simulations


TODO
