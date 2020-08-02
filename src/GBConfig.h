#ifndef __GB_CONFIG_H__
#define __GB_CONFIG_H__
#include<string>
#include<iostream>

struct GasBoxConfig {
    int num_atoms;
    int rng_seed;
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    double z_min;
    double z_max;
    double move_dist;

 
    void
    parse_command_line(int,char**);
};

#endif // __GB_CONFIG_H__
