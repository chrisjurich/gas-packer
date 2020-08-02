#include"GBConfig.h"

void
GasBoxConfig::parse_command_line(int argc,char** argv) {
    
    const auto not_found = std::string::npos;
    
    for(auto it = 1; it<argc; it += 2 ) { 
        auto option = std::string(argv[it]);
         
        auto token = it+1 < argc ? std::string(argv[it+1]) : std::string("") ; 
        if(option.find("help") != not_found || option == "h")
        {
            std::cout<<"Gas Box Configuration\n";
            std::cout<<std::string(50,'-')<<"\n";
            std::cout<<"Options include:\n"\
                "-atoms => number of atoms in simulation\n"\
                "-rng => integer seed for random number generator\n"\
                "-xmin => min x coordinate in box\n"
                "-xmax => max x coordinate in box\n"
                "-ymin => min y coordinate in box\n"
                "-ymax => max y coordinate in box\n"
                "-zmin => min z coordinate in box\n"
                "-zmax => max z coordinate in box\n";
            exit(0);
        }
        else if(option.find("atoms") != not_found) 
        {
            num_atoms = std::stoi(token);
        }
        else if (option.find("rng") != not_found) 
        {
            rng_seed = std::stoi(token);
        } 
        else if (option.find("xmin") != not_found)
        {
            x_min = std::stod(token);
        } 
        else if (option.find("xmax") != not_found)
        {
            x_max = std::stod(token);
        } 
        else if (option.find("ymin") != not_found)
        {
            y_min = std::stod(token);
        } 
        else if (option.find("ymax") != not_found)
        {
            y_max = std::stod(token);
        } 
        else if (option.find("zmin") != not_found)
        {
            z_min = std::stod(token);
        } 
        else if (option.find("zmax") != not_found)
        {
            z_max = std::stod(token);
        } 
        else if (option.find("move") != not_found)
        {
            move_dist= std::stod(token);
        } 
        else 
        {
            std::cout<<"Unexpected argument "<<option<<" exiting program"<<std::endl;
            exit(100);
        }
    }

}

