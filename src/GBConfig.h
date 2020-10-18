#ifndef __GB_CONFIG_H__
#define __GB_CONFIG_H__

#include <string>
#include <iostream>

struct GasBoxConfig {
    std::string outfile ;
    int num_atoms ;
    int rng_seed ; 
    int num_moves ;
    double x_min ;
    double x_max ;
    double y_min ;
    double y_max ;
    double z_min ;
    double z_max ;
    double move_dist ;

 
    GasBoxConfig() :
        outfile("NA"),
        num_atoms(100),
        rng_seed(1835135135),
        num_moves(1000),
        x_min(0.),
        x_max(10.),
        y_min(0.),
        y_max(10.),
        z_min(0.),
        z_max(10.),
        move_dist(1) {}
    void
    parse_command_line(int,char**);
};

#endif // __GB_CONFIG_H__
