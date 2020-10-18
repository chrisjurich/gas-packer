#ifndef __LJ_POTENTIAL_H_
#define __LJ_POTENTIAL_H_

#include <cmath>
#include <limits>

#include <GasAtom.h>
#include <gb_utils.h>

class LennardJonesPotential{
    private:
        const double& r_m;
    private:
        const double& ep;

    public:
        LennardJonesPotential(
                const double& r_m,
                const double& ep
                ) : 
            r_m(r_m),
            ep(ep) {}

    public:
        double
        energy(const double) const;
                    
    public:
        double
        energy(const GasAtom&, const GasAtom&) const;


};

#endif //__LJ_POTENTIAL_H_
