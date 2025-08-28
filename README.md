# 3D Physics Point Simulator

C++ command-line application that simulates N physical points under M forces in a 3D cube with VTK visualization support.

## Overview

Simulates point motion using kinematic equation `s(t) = ½at² + vt + v₀` with configurable friction, forces, and physics parameters. Outputs positions every second for T seconds.

## Build

Requirements: C++17 compiler, CMake 3.10+, VTK (optional)

```bash
mkdir build && cd build && cmake .. && make
```

Executable created in `run/` directory.

## Usage

Config file mode (recommended):
```bash
./run/3DPointSimulator <config_file>
```

Command line mode:
```bash
./run/3DPointSimulator <L> <N> <a1> <a2> <M> <amin> <amax> <vmin> <vmax> <v0min> <v0max> <T> [vtk_output_file]
```

Parameters: L=cube size, N=points, a1/a2=friction range, M=forces per point, amin/amax=acceleration range, vmin/vmax=velocity range, v0min/v0max=initial velocity range, T=time duration

### Example Config File

```ini
cube_size = 10.0
num_points = 5
min_friction = 0.1
max_friction = 0.5
num_forces = 2
min_acceleration = -2.0
max_acceleration = 2.0
min_velocity = -1.0
max_velocity = 1.0
min_initial_velocity = -0.5
max_initial_velocity = 0.5
simulation_time = 10
vtk_output_file = simulation_output
```

## VTK Output

Generates `.vtp` files for each time step and `.pvd` collection file for ParaView animation with position, velocity, acceleration, and friction data.