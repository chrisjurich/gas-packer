#ifndef __GASBOX_H__
#define __GASBOX_H__

#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>

#include <GasAtom.h>
#include <gb_utils.h>
#include <LJPotential.h>
#include <Metropolis.h>
#include <GBConfig.h>

#include <CLI/CLI.hpp>

class GasBox{
    private:
        GasBoxConfig config_;
    private:
        Dimensions box_dims;
    private:
        std::vector<GasAtom> atoms;
    private:
        std::unordered_map<std::pair<int,int>,double> last_distances;
    private:
        LennardJonesPotential lj_potential;
    private:
        MetropolisSelector mc_selector;
    private:
        std::vector<BoxSnapShot> states;
    public:
        GasBox( ) : lj_potential(r_m,epsilon),
                    mc_selector(MetropolisSelector())
                   {

                   }
    public:
        GasBox(
            int number_atoms,
            int rng_seed,
            double x_min,
            double x_max,
            double y_min,
            double y_max,
            double z_min,
            double z_max,
            double move_distance,
            std::string outfile
        ) :
            box_dims(Dimensions(x_min,
                            x_max,
                            y_min,
                            y_max,
                            z_min,
                            z_max)),
            lj_potential(r_m,epsilon),
            mc_selector(MetropolisSelector())
            {
                config_.rng_seed = rng_seed;
                config_.num_atoms = number_atoms;
                config_.move_dist = move_distance;
                config_.outfile = std::move(outfile);
                initialize();
            }
    public:
        void
        setup_options();

    public:
        void
        initialize();
    
    public:
        void
        caluclate_distances();
    
    public:
        void
        simulate();

    public:
        void
        to_csv();
    // for pybindings 
    public:
        std::vector<std::vector<Position>>
        moves();

    private:
        void
        _move_atoms();

    public:
        CLI::App app_;
};



#endif //__GASBOX_H__
