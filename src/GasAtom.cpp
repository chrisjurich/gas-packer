#include<GasAtom.h>

void
Position::apply_bounds(const Dimensions& dimensions) {

        if(x > dimensions.x_max) {
            x += (dimensions.x_min - dimensions.x_max);
        }
        if(x < dimensions.x_min) {
            x += (dimensions.x_max - dimensions.x_min);
        }
        // dealing with y dimensions 
        if(y > dimensions.y_max) {
            y += (dimensions.y_min - dimensions.y_max);
        }
        if(y < dimensions.y_min) {
            y += (dimensions.y_max - dimensions.y_min);
        }
        // dealing with z dimensions 
        if(z > dimensions.z_max) {
            z += (dimensions.z_min - dimensions.z_max);
        }
        if(z < dimensions.z_min) {
            z += (dimensions.z_max - dimensions.z_min);
        }
    }

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

double
GasAtom::distance(const Position& pos) const {
    const auto lower_x = std::min(pos.x,curr_pos.x);
    const auto upper_x = std::max(pos.x,curr_pos.x);
    const auto lower_y = std::min(pos.y,curr_pos.y);
    const auto upper_y = std::max(pos.y,curr_pos.y);
    const auto lower_z = std::min(pos.z,curr_pos.z);
    const auto upper_z = std::max(pos.z,curr_pos.z);
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
            std::pow(x_dist, 2.) +
            std::pow(y_dist, 2.) +
            std::pow(z_dist, 2.) 
            ,
            0.5);
}

GasAtom
GasAtom::proposed_move(const Position& other) const {
    auto proposed = GasAtom(
                        curr_pos.x + other.x,
                        curr_pos.y + other.y,
                        curr_pos.z + other.z,
                        dimensions,
                        -1
                        );

    return proposed;
}

void
GasAtom::_apply_bounds() {
    // dealing with x dimensions 
    if(curr_pos.x > dimensions.x_max) {
        curr_pos.x += (dimensions.x_min - dimensions.x_max);
    }
    if(curr_pos.x < dimensions.x_min) {
        curr_pos.x += (dimensions.x_max - dimensions.x_min);
    }
    // dealing with y dimensions 
    if(curr_pos.y > dimensions.y_max) {
        curr_pos.y += (dimensions.y_min - dimensions.y_max);
    }
    if(curr_pos.y < dimensions.y_min) {
        curr_pos.y += (dimensions.y_max - dimensions.y_min);
    }
    // dealing with z dimensions 
    if(curr_pos.z > dimensions.z_max) {
        curr_pos.z += (dimensions.z_min - dimensions.z_max);
    }
    if(curr_pos.z < dimensions.z_min) {
        curr_pos.z += (dimensions.z_max - dimensions.z_min);
    }
}
