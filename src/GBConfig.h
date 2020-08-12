#ifndef __GB_CONFIG_H__
#define __GB_CONFIG_H__

#include<string>
#include<iostream>

struct GasBoxConfig {
    std::string outfile = "NA";
    int num_atoms = 100;
    int rng_seed = 1835135135;
    int num_moves = 1000; 
    double x_min = 0.;
    double x_max = 10.;
    double y_min = 0.;
    double y_max = 0.;
    double z_min = 0.;
    double z_max = 10.;
    double move_dist = 1;

 
    void
    parse_command_line(int,char**);
};

#endif // __GB_CONFIG_H__
