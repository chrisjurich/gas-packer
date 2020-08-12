#include <iostream>
#include <GBConfig.h>
#include <GasBox.h>


int main(int argc, char** argv) {
    
    auto config = GasBoxConfig();
    config.parse_command_line(argc,argv);
    
    auto gb = GasBox(config); 
    gb.initialize();
    gb.simulate(config.num_moves);
    gb.to_csv();
}
