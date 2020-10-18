#include <GasBox.h>

void
GasBox::setup_options() {

    app_.add_option("--outfile",config_.outfile)
        ->required()
        ->description("The file where the trajectories will be saved. WILL overwrite existing files.");

    app_.add_option("--num_atoms", config_.num_atoms)
        ->default_val(100)
        ->check(CLI::PositiveNumber)
        ->description("The number of atoms used in the Gas Box. Note that increasing this number will increase the run time of the simulation significantly.");

    app_.add_option("--rng_seed", config_.rng_seed)
        ->default_val(1835135135)
        ->check(CLI::PositiveNumber)
        ->description("The number to which the systems Random Number Generator will be seeded.");

    app_.add_option("--num_moves")
        ->default_val(1000)
        ->check(CLI::PositiveNumber)
        ->description("The number of moves that each atom will make. Note that increasing this number will increase the run time of the simulation significantly.");

    app_.add_option("--x_min",config_.x_min)
        ->default_val(0.)
        ->check(CLI::Number)
        ->description("The lower x bound of the gas box. MUST be smaller than x_max.");

    app_.add_option("--x_max",config_.x_max)
        ->default_val(10.)
        ->check(CLI::Number)
        ->description("The upper x bound of the gas box. MUST be larger than x_min.");

    app_.add_option("--y_min",config_.y_min)
        ->default_val(0.)
        ->check(CLI::Number)
        ->description("The lower y bound of the gas box. MUST be smaller than y_max.");

    app_.add_option("--y_max",config_.y_max)
        ->default_val(10.)
        ->check(CLI::Number)
        ->description("The upper y bound of the gas box. MUST be larger than y_min.");

    app_.add_option("--z_min",config_.z_min)
        ->default_val(0.)
        ->check(CLI::Number)
        ->description("The upper z bound of the gas box. MUST be smaller than z_max.");

    app_.add_option("--z_max",config_.z_max)
        ->default_val(10.)
        ->check(CLI::Number)
        ->description("The lower z bound of the gas box. MUST be larger than z_min.");

    app_.add_option("--move_dist",config_.move_dist)
        ->default_val(1.)
        ->check(CLI::PositiveNumber)
        ->description("The maximum distance an atom can move in any one direction in a given move");

}

void
GasBox::initialize() {
    // check to make sure that the
    auto bad_dims(0);
    if( config_.x_min >= config_.x_max) {
        ++bad_dims;
        std::cerr<<"ERROR: x_min MUST be less than x_max. Current values x_min: "<<std::setprecision(8)<<config_.x_min<<" x_max: "<<config_.x_max;
    } else if( config_.y_min >= config_.y_max) {
        ++bad_dims;
        std::cerr<<"ERROR: y_min MUST be less than y_max. Current values y_min: "<<std::setprecision(8)<<config_.y_min<<" y_max: "<<config_.y_max;
    } else if( config_.z_min >= config_.z_max) {
        ++bad_dims;
        std::cerr<<"ERROR: z_min MUST be less than z_max. Current values z_min: "<<std::setprecision(8)<<config_.z_min<<" z_max: "<<config_.z_max;
    }

    if(bad_dims) {
        std::cerr<<"Check the box dimenstions and re-run the application. Exiting...";
        exit(1);
    }
    // assign data
    last_distances.reserve(
            config_.num_atoms*(config_.num_atoms-1)/2
    );
    // seed the srand
    srand(config_.rng_seed^0x09101996);
    // initializes the GasAtom vector
    for(auto atom_num = 0; atom_num < config_.num_atoms; ++atom_num){
        // time to generate the random (x,y,z) points for the atoms
        // first x 
        const auto x = (static_cast<double>(rand())/RAND_MAX)*(box_dims.x_max-box_dims.x_min) + box_dims.x_min;
        // then y 
        const auto y = (static_cast<double>(rand())/RAND_MAX)*(box_dims.y_max-box_dims.y_min) + box_dims.y_min;
        // then z
        const auto z = (static_cast<double>(rand())/RAND_MAX)*(box_dims.z_max-box_dims.z_min) + box_dims.z_min;
        // now make the GasAtomObject
        atoms.emplace_back(x,y,z,box_dims,atom_num);
    }
   
    caluclate_distances();
}

void
GasBox::caluclate_distances() {
    // helper method that finds the cross distances between all the points 
    for(auto first_index = 0; first_index < config_.num_atoms; ++first_index) {
        for(auto second_index = 0; second_index < config_.num_atoms; ++second_index) {
            if(first_index != second_index){
                const auto lower_index = std::min(first_index,second_index);
                const auto upper_index = std::max(first_index,second_index);
                last_distances[
                    {lower_index,upper_index}
                    ] = atoms[lower_index].distance(atoms[upper_index]);
            } 
        }
    }

}

void
GasBox::to_csv() {
    
    auto out = std::ofstream(config_.outfile);
    auto positions = std::vector<std::vector<Position>>();
    out<<"move";
    for(const auto& atom : atoms) {
        out<<","<<atom.id();
        positions.push_back(atom.positions());
    }
    out<<'\n';
    const auto num_moves = positions[0].size();
    for(auto move_it = 0; move_it < num_moves; ++ move_it) {
        out<<move_it;
        for(auto& col : positions) {
            out<<','<<col[move_it].to_string(); 
        }
        out<<'\n';
    }

    out.close();

}
std::vector<std::vector<Position>>
GasBox::moves() {
    auto positions = std::vector<std::vector<Position>>();
    positions.reserve(atoms.size()); 
    
    for(const auto& atom : atoms ) {
        positions.push_back(atom.positions());
    }

    return positions;
}


void
GasBox::_move_atoms() {
    
    auto snapshot = BoxSnapShot();

    const auto num_atoms = atoms.size(); 
    auto moves = std::vector<Position>(num_atoms);
    caluclate_distances(); 
    for(auto atom_it = 0; atom_it<num_atoms; ++atom_it){
        // calculate original energy 
        auto energy = double(0.);
        for(const auto& index_pair_distance : last_distances) {
            if (atom_it == index_pair_distance.first.first or
                    atom_it == index_pair_distance.first.second ) {
                energy += lj_potential.energy(
                    atoms[index_pair_distance.first.first],
                    atoms[index_pair_distance.first.second]
                        );
            }
        
        }

        const auto atom_move = Position(
                                    config_.move_dist*((static_cast<double>(rand())/RAND_MAX)*2. - 1.),
                                    config_.move_dist*((static_cast<double>(rand())/RAND_MAX)*2. - 1.),
                                    config_.move_dist*((static_cast<double>(rand())/RAND_MAX)*2. - 1.)
                                    );
        
        auto candidate_energy = double(0.); 
        const auto proposed = atoms[atom_it].proposed_move(atom_move);
        
        for(auto other_it = 0; other_it < num_atoms; ++other_it) {
            if(other_it == atom_it) {
                continue;     
            }
            candidate_energy += lj_potential.energy(
                    proposed.distance(atoms[other_it])
                    );

        }

        if(candidate_energy <= energy) {
            snapshot.accepted_moves += 1;
            moves[atom_it] = atom_move;         
        } else if (mc_selector.accept_move(candidate_energy/energy)){
            snapshot.accepted_moves += 1;
            moves[atom_it] = atom_move;
        } else {
            snapshot.rejected_moves += 1;
            moves[atom_it] = Position(0.,0.,0.);
        }
    }

    for(auto atom_it =0; atom_it<num_atoms; ++atom_it) {
        atoms[atom_it] += moves[atom_it];
    }
    
    states.push_back(snapshot);
}

void
GasBox::simulate() {
    initialize();
    for (int step = 0; step < config_.num_atoms; ++step) {
        _move_atoms();

    }
    to_csv();
}