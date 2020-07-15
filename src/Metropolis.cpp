#include<Metropolis.h>

bool
MetropolisSelector::accept_move(double percentage) {
    if(percentage <= 1.) {
        return true;
    }

    const auto threshold = std::pow(e,-percentage);
            
    return  static_cast<double>(rand())/RAND_MAX*1. < threshold;

}
