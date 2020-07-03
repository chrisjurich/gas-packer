








#include<GasAtom.h>


double
GasAtom::distance(const GasAtom& other) const {
    
    return std::pow(
            std::pow(other.curr_pos.x - curr_pos.x,2.) + \ 
            std::pow(other.curr_pos.y - curr_pos.y, 2.) + \
            std::pow(other.curr_pos.z - curr_pos.z, 2.) 
            ,
            0.5);

}

