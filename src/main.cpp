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
    gb.initialize();

}
