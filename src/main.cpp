#include <iostream>
#include <GBConfig.h>
#include <GasBox.h>


int main(int argc, char** argv) {

    auto gb = GasBox();
    gb.setup_options();
    CLI11_PARSE(gb.app_,argc,argv);
    gb.simulate();
}
