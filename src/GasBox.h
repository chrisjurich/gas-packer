#ifndef __GASBOX_H__
#define __GASBOX_H__

#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>

#include <GasAtom.h>

class GasBox{
    private:
        double x_min, x_max, y_min, y_max, z_min, z_max;
    private:
        int number_atoms, rng_seed;
    private:
        std::vector<GasAtom> atoms;
    
    public:
        GasBox(
            int number_atoms,
            int rng_seed, 
            double x_min,
            double x_max,
            double y_min,
            double y_max,
            double z_min,
            double z_max
               ) : number_atoms(number_atoms), rng_seed(rng_seed),
                   x_min(x_min), x_max(x_max),
                   y_min(y_min), y_max(y_max),
                   z_min(z_min), z_max(z_max) {
                    // seeding the rng 
                    srand(rng_seed);
                   }

        
    public:
        void
        initialize();
};








#endif //__GASBOX_H__
