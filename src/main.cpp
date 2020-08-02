#include<iostream>
#include<GBConfig.h>
#include<GasBox.h>


int main(int argc, char** argv) {
    auto config = GasBoxConfig();
    config.parse_command_line(argc,argv);
    return 0;
    auto gb = GasBox(
                    100, // number atoms
                    10, // rng seed
                    0., // x min
                    10., // x max
                    0., // y min
                    10., // y max
                    0., // z min
                    10., // z max
                    1
                    );
    std::cout<<"created"<<std::endl; 
    gb.initialize();
    std::cout<<"Initizlized"<<std::endl;
    gb.simulate(1000);
    std::cout<<"simulated one step"<<std::endl;
    gb.to_csv("../data/multiple_atoms.csv");
}
