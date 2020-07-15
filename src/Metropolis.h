#ifndef __METROPOLIS_H__
#define __METROPOLIS_H__

#include <cstdlib>
#include <cmath>

#include <gb_utils.h>

class MetropolisSelector{
    
    public:
        //constructor
        MetropolisSelector() {

        }

    public:
        bool
        accept_move(double);

    


};
#endif // __METROPOLIS_H__
