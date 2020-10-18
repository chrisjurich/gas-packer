import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation
import argparse

from cj_gas_packer import GasBox


def convert_positions_to_data(positions_matrix):
    """
    Converts the output from the C++ bindings to a usable matrix of position information. 
    Takes the C++ binding output as input and returns the usable data matrix.
    """
    # this part gets a little weird bc of how the data is outputted
    atom_moves = list()
    for move_index in range(len(positions_matrix[0])):
        row_coords = []
        for atom_index in range(len(positions_matrix)):
            pos = positions_matrix[atom_index][move_index]
            row_coords.append(
                [pos.x, pos.y, pos.z]
            )
        atom_moves.append(np.array(row_coords))

    return atom_moves


def animate_scatters(iteration, data, scatters):
    """
    Update the data held by the scatter plot and therefore animates it.
    Args:
        iteration (int): Current iteration of the animation
        data (list: List of the data positions at each iteration.
        scatters (list): List of all the scatters (One per element)
    Returns:
        list: List of scatters (One per element) with new coordinates
    """
    for i in range(data[0].shape[0]):
        scatters[i]._offsets3d = (data[iteration][i, 0:1], data[iteration][i, 1:2], data[iteration][i, 2:])
    return scatters


def add_outline(ax, x_min, x_max, y_min, y_max, z_min, z_max):
    """
    Method that adds the outline of the Gas Box to the axes in 3D
    """
    ax.plot([x_min, x_min], [y_min, y_min], [z_min, z_max], c='black')
    ax.plot([x_max, x_max], [y_min, y_min], [z_min, z_max], c='black')
    ax.plot([x_min, x_min], [y_max, y_max], [z_min, z_max], c='black')
    ax.plot([x_max, x_max], [y_max, y_max], [z_min, z_max], c='black')

    ax.plot([x_min, x_max], [y_min, y_min], [z_min, z_min], c='black')
    ax.plot([x_min, x_max], [y_max, y_max], [z_min, z_min], c='black')
    ax.plot([x_min, x_max], [y_min, y_min], [z_max, z_max], c='black')
    ax.plot([x_min, x_max], [y_max, y_max], [z_max, z_max], c='black')

    ax.plot([x_min, x_min], [y_min, y_max], [z_min, z_min], c='black')
    ax.plot([x_max, x_max], [y_min, y_max], [z_min, z_min], c='black')
    ax.plot([x_min, x_min], [y_min, y_max], [z_max, z_max], c='black')
    ax.plot([x_max, x_max], [y_min, y_max], [z_max, z_max], c='black')


def get_simulation_data(input_params):
    """
    Core method that gets the trajectories for each atom. Takes a params object as input (see setup_options())
    for details. Returns the number of atoms as well as the moves that occur.
    """
    box = GasBox(
        input_params.num_atoms,
        input_params.rng_seed,
        input_params.num_moves,
        input_params.x_min,
        input_params.x_max,
        input_params.y_min,
        input_params.y_max,
        input_params.z_min,
        input_params.z_max,
        input_params.move_dist,
        input_params.outfile
    )
    box.simulate()
    return input_params.num_atoms, box.moves()


def main(params):
    """
    Creates the 3D figure and animates it with the input the output data created from input params.
    Input params object contains the relevant information to be fed to the GasBox. See setup_options() for more info
    """
    num_atoms, moves = get_simulation_data(params)  # alternative way (target way actually) to get the data
    data = convert_positions_to_data(moves)
    # Attaching 3D axis to the figure
    fig = plt.figure()
    ax = p3.Axes3D(fig)
    ax.grid(False)
    # Initialize scatters
    scatters = [ax.scatter(data[0][i, 0:1], data[0][i, 1:2], data[0][i, 2:], color='blue') for i in
                range(data[0].shape[0])]
    add_outline(ax, params.x_min, params.x_max, params.y_min, params.y_max, params.z_min, params.z_max)

    # Number of iterations
    iterations = len(data)
    # Setting the axes properties
    global_max = max(params.x_max, params.y_max, params.z_max)
    global_min = min(params.x_min, params.y_min, params.z_min)

    ax.set_xlim3d([global_min, global_max])

    ax.set_ylim3d([global_min, global_max])

    ax.set_zlim3d([global_min, global_max])

    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)
    ax.w_xaxis.set_pane_color((1.0, 1.0, 1.0, 0.0))
    ax.w_yaxis.set_pane_color((1.0, 1.0, 1.0, 0.0))
    ax.w_zaxis.set_pane_color((1.0, 1.0, 1.0, 0.0))
    ax.w_xaxis.line.set_color((1.0, 1.0, 1.0, 0.0))
    ax.w_yaxis.line.set_color((1.0, 1.0, 1.0, 0.0))
    ax.w_zaxis.line.set_color((1.0, 1.0, 1.0, 0.0))  # Provide starting angle for the view.

    ani = animation.FuncAnimation(fig, animate_scatters, iterations, fargs=(data, scatters),
                                  interval=200, blit=True, repeat=False)
    Writer = animation.writers['ffmpeg']
    writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800, extra_args=['-vcodec', 'libx264'])
    ani.save(params.video, writer=writer)


def setup_options():
    """
    Helper method that sets up the commandline options for the simulation and then parses
    the commandline. Additionally it performs checks on the supplied values.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("-outfile", type=str, required=False, default="NONE", help="Output csv for simulation data")
    parser.add_argument("-video", type=str, required=True, help='The file where the video will be saved')
    parser.add_argument("-num_atoms", type=int, default=100, help='The number of atoms in the GasBox. Default is 100. '
                                                                  'Larger numbers will lead to slower runtimes.')

    parser.add_argument("-x_min", type=float, default=0., help='Lower x bound. MUST be less than x_max')
    parser.add_argument("-x_max", type=float, default=10., help='Upper x bound. MUST be greater than x_min')

    parser.add_argument("-y_min", type=float, default=0., help='Lower y bound. MUST be less than y_max')
    parser.add_argument("-y_max", type=float, default=10., help='Upper y bound. MUST be greater than y_min')

    parser.add_argument("-z_min", type=float, default=0., help='Lower z bound. MUST be less than z_max')
    parser.add_argument("-z_max", type=float, default=10., help='Upper z bound. MUST be greater than z_min')
    parser.add_argument("-rng_seed", type=int, default=1835135135, help='The number to which the System\'s random '
                                                                        'number generator will be seeded')
    parser.add_argument("-num_moves", type=int, default=1000, help='The number of moves that each atom will make. '
                                                                   'Larger  numbers will lead to slower runtimes.')
    parser.add_argument("-move_dist", type=float, default=1.0, help='Maximum distance that any one atom can move in a '
                                                                    'direction. MUST be > 0')

    args = parser.parse_args()

    bad_dims = 0
    if args.x_min >= args.x_max:
        bad_dims += 1
        print(f"ERROR: x_min is NOT less than x_max. x_min: {args.x_min:.3f} x_max: {args.x_max:.3f}")

    if args.y_min >= args.y_max:
        bad_dims += 1
        print(f"ERROR: y_min is NOT less than y_max. y_min: {args.y_min:.3f} y_max: {args.y_max:.3f}")

    if args.x_min >= args.x_max:
        bad_dims += 1
        print(f"ERROR: x_min is NOT less than x_max. x_min: {args.x_min:.3f} x_max: {args.x_max:.3f}")

    if args.move_dist <= 0:
        bad_dims += 1
        print(f"ERROR: move_dist MUST be positive. move_dist: {args.move_dist:.3f}")

    if args.num_moves <= 0:
        bad_dims += 1
        print(f"ERROR: num_moves MUST be positive. num_moves: {args.num_moves:.3f}")

    if args.num_atoms <= 0:
        bad_dims += 1
        print(f"ERROR: num_atoms MUST be positive. num_atoms: {args.num_atoms:.3f}")

    if bad_dims > 0:
        print("Fix gas box dimensions before running script again. Exiting...")
        exit(1)

    return args


if __name__ == "__main__":
    options = setup_options()
    main(options)