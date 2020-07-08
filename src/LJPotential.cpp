#include<LJPotential.h>



double
LennardJonesPotential::energy(const double distance) const {

    return 4*ep*(
            std::pow(r_m/distance,12.) - std::pow(r_m/distance,6.)
            );
}

double
LennardJonesPotential::energy(const GasAtom& ga1, const GasAtom& ga2) const {
    
    const auto dist = ga1.distance(ga2);
    return energy(dist);
}
