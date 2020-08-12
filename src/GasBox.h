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

class GasBox{
    private:
        Dimensions box_dims;
    private:
        int number_atoms, rng_seed;
    private:
        std::vector<GasAtom> atoms;
    private:
        std::unordered_map<std::pair<int,int>,double> last_distances;
    private:
        LennardJonesPotential lj_potential;
    private:
        MetropolisSelector mc_selector;
    private:
        double move_distance;
    private:
        std::vector<BoxSnapShot> states;
    private: 
        std::string outfile;
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
               ) : number_atoms(number_atoms), rng_seed(rng_seed),
                    box_dims(Dimensions(x_min,
                                        x_max,
                                        y_min,
                                        y_max,
                                        z_min,
                                        z_max)),
                    lj_potential(r_m,epsilon),
                    mc_selector(MetropolisSelector()),
                    move_distance(move_distance),
                    outfile(outfile)
                   {
                    // seeding the rng 
                    srand(rng_seed);
                    // reserving the appropriate size for the last_distances umap
                    last_distances.reserve(
                        number_atoms*(number_atoms-1)/2
                            );
                   }
        
        GasBox(const GasBoxConfig& config) :
                number_atoms(config.num_atoms),
                rng_seed(config.rng_seed),
                box_dims(Dimensions(
                                    config.x_min,
                                    config.x_max,
                                    config.y_min,
                                    config.y_max,
                                    config.z_min,
                                    config.z_max)),
                lj_potential(r_m,epsilon),
                mc_selector(MetropolisSelector()),
                move_distance(config.move_dist),
                outfile(config.outfile)
                {
                    // seeding the rng 
                    srand(rng_seed);
                    // reserving the appropriate size for the last_distances umap
                    last_distances.reserve(
                        number_atoms*(number_atoms-1)/2
                            );
            
                }
        
    public:
        void
        initialize();
    
    public:
        void
        caluclate_distances();
    
    public:
        void
        simulate(int);

    public:
        void
        to_csv();
    
    private:
        void
        _move_atoms();

};



#endif //__GASBOX_H__
