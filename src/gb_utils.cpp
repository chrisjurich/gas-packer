#include<gb_utils.h>





double
rms_velocity(double kelvin, double molar_mass=1.,double gas_constant=R) {
    if(kelvin <= 0 ||  molar_mass <= 0) {
        throw BadValue(std::string("temperature and molar_mass must be greater than or equal to zero"));
    }
    return std::sqrt(3.*kelvin/molar_mass);
}
