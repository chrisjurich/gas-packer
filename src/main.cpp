#include<GasAtom.h>
#include<iostream>




int main() {
    
    auto GA1 = GasAtom(1,2,3,"Atom1");
    auto GA2 = GasAtom(0,0,0,"Atom2");

    std::cout<<GA1.distance(GA2)<<std::endl;
    

}
