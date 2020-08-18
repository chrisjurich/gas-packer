import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation

from gas_packer import GasBoxConfig, GasBox

def gas_positions(csv):
    df = pd.read_csv(csv)
    atom_moves = list()
    for index, row in df.iterrows():
        row_coords = list()
        for value in row:
            if isinstance(value,str):
                row_coords.append(
                [float(tk) for tk in value.split('|')]
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
        scatters[i]._offsets3d = (data[iteration][i,0:1], data[iteration][i,1:2], data[iteration][i,2:])
    return scatters

def add_outline(ax,start,end):
        ax.plot([start,end],[start,start],[start,start],c='black')
        ax.plot([start,end],[end,end],[end,end],c='black')
        ax.plot([start,end],[end,end],[start,start],c='black')
        ax.plot([start,end],[start,start],[end,end],c='black')

        ax.plot([end,end],[end,start],[end,end],c='black')
        ax.plot([start,start],[start,end],[start,start],c='black')
        ax.plot([end,end],[end,start],[start,start],c='black')
        ax.plot([start,start],[start,end],[end,end],c='black')

        ax.plot([end,end],[start,start],[start,end],c='black')
        ax.plot([start,start],[start,start],[start,end],c='black')
        ax.plot([start,start],[end,end],[start,end],c='black')
        ax.plot([end,end],[end,end],[start,end],c='black')

def get_simulation_data(num_moves):
    config = GasBoxConfig()
    box = GasBox(config)
    box.initialize()
    box.simulate(num_moves)
    return GasBoxConfig.num_atoms, box.moves()

def main(data, save=False):
    """
    Creates the 3D figure and animates it with the input data.
    Args:
        data (list): List of the data positions at each iteration.
        save (bool): Whether to save the recording of the animation. (Default to False).
    """
    num_atoms, moves = get_simulation_data(10) # alternative way (target way actually) to get the data
    # Attaching 3D axis to the figure
    fig = plt.figure()
    ax = p3.Axes3D(fig)
    ax.grid(False)
    # Initialize scatters
    scatters = [ ax.scatter(data[0][i,0:1], data[0][i,1:2], data[0][i,2:],color='blue') for i in range(data[0].shape[0]) ]
    add_outline(ax,0,10)

    # Number of iterations
    iterations = len(data)

    # Setting the axes properties

    ax.set_xlim3d([0,10])
    ax.set_xlim3d()
    #ax.set_xlabel('X')

    ax.set_ylim3d([0,10])
    #ax.set_ylabel('Y')

    ax.set_zlim3d([0,10])
    ax.set_zlim3d()
    #ax.set_zlabel('Z')

    #ax.set_title('ideal_gas_simulation')
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_zticks([])
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)
    ax.w_xaxis.set_pane_color((1.0, 1.0, 1.0, 0.0))
    ax.w_yaxis.set_pane_color((1.0, 1.0, 1.0, 0.0))
    ax.w_zaxis.set_pane_color((1.0, 1.0, 1.0, 0.0))
    ax.w_xaxis.line.set_color((1.0, 1.0, 1.0, 0.0))
    ax.w_yaxis.line.set_color((1.0, 1.0, 1.0, 0.0))
    ax.w_zaxis.line.set_color((1.0, 1.0, 1.0, 0.0))# Provide starting angle for the view.

    ani = animation.FuncAnimation(fig, animate_scatters, iterations, fargs=(data, scatters),
                                       interval=50, blit=False, repeat=True)

    if save:
        Writer = animation.writers['ffmpeg']
        writer = Writer(fps=30, metadata=dict(artist='Me'), bitrate=1800, extra_args=['-vcodec', 'libx264'])
        ani.save('final_params.mp4', writer=writer)

    #plt.show()

if __name__ == "__main__":

    main()
    #data = gas_positions("../data/multiple_atoms.csv")

    ##print(generate_data(1000, 2))
    #main(data, save=True)
