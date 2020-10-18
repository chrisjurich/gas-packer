# Gas Packer
This is a toy project that packs a set of gas molcules into a box using a Monte Carlo algorithm and produces an animation.

Example output: [Youtube](https://youtu.be/Z7GWBJKAAQQ)
## Install

There are two options for installation: native C++ code and python bindings.
Using python is recommended as this allows the user to easily generate an .mp4 animation. 

Because this project uses pybind11 as a submodule, the cloning command is: `git clone --recurse-submodules https://github.com/chrisjurich/gas-packer.git`

## Dependencies

Python: python >= 3.0 (all development done in 3.8), numpy, pandas, matplotlib, matplotlib.mplot3d, matplotlib.animation

C++: C++17, CMake, (optional) Ninja

System: ffmpeg

### Native C++
This project is built using C++17 as well as CMake and Ninja. It will compile with clang or gcc. The following command compiles the source code:


`$ cd build && cmake [-G Ninja] .. && [Ninja|Make]`

If you do not want to compile the CJ-GAS-PACKER executable, you can pass the option `-DCPP=OFF` during CMake generation.
If you are having issues with this step, deleting `CMakeCache.txt` will often help.

### Python Bindings
This project also supports python bindings with [pybind11](https://github.com/pybind/pybind11). This installation requires CMake, a working compiler and is only tested for python3. To install the bindings, use the following command:


`$ pip install . --user`


The module can then be imported with: 

`import cj_gas_packer`

although the easier option is to use the `src/anim.py` script that already has the code setup.
Note that the above pip statement MUST be called even if you are going to use the pre-created script.
## Running Simulations

### Native C++
Simulations can be run using the CJ-GAS-PACKER binary which will be left in the root directory if the CMake build went well.
The performance of the program is highly tunable, and below are the commandline options that can be used to alter performance.
```
  --outfile TEXT REQUIRED     The file where the trajectories will be saved. WILL overwrite existing files.
  --num_atoms INT:POSITIVE=100
                              The number of atoms used in the Gas Box. Note that increasing this number will increase the run time of the simulation significantly.
  --rng_seed INT:POSITIVE=1835135135
                              The number to which the systems Random Number Generator will be seeded.
  --num_moves :POSITIVE=1000  The number of moves that each atom will make. Note that increasing this number will increase the run time of the simulation significantly.
  --x_min FLOAT:NUMBER=0      The lower x bound of the gas box. MUST be smaller than x_max.
  --x_max FLOAT:NUMBER=10     The upper x bound of the gas box. MUST be larger than x_min.
  --y_min FLOAT:NUMBER=0      The lower y bound of the gas box. MUST be smaller than y_max.
  --y_max FLOAT:NUMBER=10     The upper y bound of the gas box. MUST be larger than y_min.
  --z_min FLOAT:NUMBER=0      The upper z bound of the gas box. MUST be smaller than z_max.
  --z_max FLOAT:NUMBER=10     The lower z bound of the gas box. MUST be larger than z_min.
  --move_dist FLOAT:POSITIVE=1

```
To see the above options in the terminal, run the command `./CJ-GAS-PACKER --help`.
Once a run is complete, results can be found in the path specified by `--outfile`

An example command is `./CJ-GAS-PACKER --outfile my_data.csv`
### Python Bindings

The easiest way to run the gas packer is via the python bindings.
The script at `src/anim.py` functions essentially identically to the binary executable, with the exception of an additional commandline option for the output video file.
See the commandline options below:
```
  -outfile OUTFILE      Output csv for simulation data
  -video VIDEO          The file where the video will be saved
  -num_atoms NUM_ATOMS  The number of atoms in the GasBox. Default is 100. Larger numbers will lead to slower runtimes.
  -x_min X_MIN          Lower x bound. MUST be less than x_max
  -x_max X_MAX          Lower x bound. MUST be greater than x_min
  -y_min Y_MIN          Lower y bound. MUST be less than y_max
  -y_max Y_MAX          Lower y bound. MUST be greater than y_min
  -z_min Z_MIN          Lower z bound. MUST be less than z_max
  -z_max Z_MAX          Lower z bound. MUST be greater than z_min
  -rng_seed RNG_SEED    The number to which the System's random number generator will be seeded
  -num_moves NUM_MOVES  The number of moves that each atom will make. Larger numbers will lead to slower runtimes.
  -move_dist MOVE_DIST  Maximum distance that any one atom can move in a direction. MUST be > 0

```
An example command is `python src/anim.py -video my_video.mp4`
## Common Problems
+ If you are having problems with CMake, its usually a good idea to delete `CMakeCache.txt` and build from scratch.
+ The `src/anim.py` file will often fail if there are issues with ffmpeg. This typically occurs in the last step. If using Anaconda, this can be caused by a higher version of the .so library file being available than what is expected. This can be overcome by creating a symlink.
