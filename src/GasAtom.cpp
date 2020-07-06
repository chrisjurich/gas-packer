








#include<GasAtom.h>


double
GasAtom::distance(const GasAtom& other) const {
    // note that this distance is circular 
    const auto lower_x = std::min(other.curr_pos.x,curr_pos.x);
    const auto upper_x = std::max(other.curr_pos.x,curr_pos.x);
    const auto lower_y = std::min(other.curr_pos.y,curr_pos.y);
    const auto upper_y = std::max(other.curr_pos.y,curr_pos.y);
    const auto lower_z = std::min(other.curr_pos.z,curr_pos.z);
    const auto upper_z = std::max(other.curr_pos.z,curr_pos.z);
    // now find the x,y,z distances 
    const auto x_dist = std::min(
            upper_x - lower_x,
            dimensions.x_max - upper_x + lower_x - dimensions.x_min
            );
    const auto y_dist = std::min(
            upper_y - lower_y,
            dimensions.y_max - upper_y + lower_y - dimensions.y_min
            );
    const auto z_dist = std::min(
            upper_z - lower_z,
            dimensions.z_max - upper_z + lower_z - dimensions.z_min
            );
    return std::pow(
            std::pow(x_dist,2.) +
            std::pow(y_dist, 2.) +
            std::pow(z_dist, 2.) 
            ,
            0.5);

}

