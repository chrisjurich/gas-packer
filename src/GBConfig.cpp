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
                "-outfile => name of output file for the .csv (REQUIRED)\n"\
                "-atoms => number of atoms in simulation (optional)\n"\
                "-rng => integer seed for random number generator (optional)\n"\
                "-xmin => min x coordinate in box (optional)\n"
                "-xmax => max x coordinate in box (optional)\n"
                "-ymin => min y coordinate in box (optional)\n"
                "-ymax => max y coordinate in box (optional)\n"
                "-zmin => min z coordinate in box (optional)\n"
                "-zmax => max z coordinate in box (optional)\n";
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
        } else if (option.find("ymax") != not_found)
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
        else if (option.find("num_moves") != not_found)
        {
            num_moves = std::stoi(token);
        }
        else if (option.find("move") != not_found)
        {
            move_dist= std::stod(token);
        } 
        else if (option.find("outfile") != not_found) 
        {
            outfile = token;
        }
        else 
        {
            std::cout<<"Unexpected argument "<<option<<" exiting program"<<std::endl;
            exit(10000); 
        }
    }

    if (outfile == "NA")
    {
        std::cout<<"Missing the follwing command line argument:"<<std::endl;
        std::cout<<"\t-outfile => name of output file for the .csv (REQUIRED)"<<std::endl;
        std::cout<<"This is a required argument, program now exiting"<<std::endl;
        exit(0);
    }

}

