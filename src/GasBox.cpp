




#include "GasBox.h"


void
GasBox::initialize() {
    // initializes the GasAtom vector

    for(auto atom_num = 0; atom_num < number_atoms; ++atom_num){
        // time to generate the random (x,y,z) points for the atoms
        // first x 
        const auto x = (static_cast<double>(rand())/RAND_MAX)*(x_max-x_min) + x_min;
        // then y 
        const auto y = (static_cast<double>(rand()) /RAND_MAX)*(y_max-y_min) + y_min;
        // then z
        const auto z = (static_cast<double>(rand())/RAND_MAX)*(z_max-z_min) + z_min;
        // now make the GasAtomObject
        atoms.emplace_back(x,y,z,"atom_" + std::to_string(atom_num +1));
    }

    for(const auto& a : atoms)
        std::cout<<a;
}
