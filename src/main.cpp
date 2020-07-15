#include<iostream>

#include<GasBox.h>


int main() {
    
    auto gb = GasBox(
                    1000, // number atoms
                    10, // rng seed
                    0., // x min
                    10., // x max
                    0., // y min
                    10., // y max
                    0., // z min
                    10. // z max
                    );
    std::cout<<"created"<<std::endl; 
    gb.initialize();
    std::cout<<"Initizlized"<<std::endl;
    gb.simulate(1);
    std::cout<<"simulated one step"<<std::endl;
}
