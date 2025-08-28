# 3D Physics Point Simulation

A C++ command-line application that simulates the motion of physical points under forces in a 3D space with optional VTK visualization support.

## Overview

The 3D Physics Point Simulator simulates N physical points randomly placed inside a cube of side length L centered at the origin. Each point is subject to M forces, with motion described by the kinematic equation:

```
s(t) = ½at² + vt + v₀
```

where:
- `a` is acceleration
- `v` is velocity  
- `v₀` is initial velocity

Each point has its own friction coefficient and properties randomly chosen within specified ranges. The simulation outputs point positions every second for T seconds.

## Features

- **3D Physics Simulation**: Realistic point motion with acceleration, velocity, and friction
- **Configurable Parameters**: All simulation parameters can be customized via command line
- **VTK Output**: Optional 3D visualization files for ParaView, VisIt, and other VTK-compatible viewers
- **Time Series Data**: Complete temporal evolution of all points with full physics properties
- **Clean Architecture**: Well-structured C++ classes with separation of concerns

## Architecture

### Core Classes

#### `Vector3D`
- Header-only 3D vector mathematics class
- Supports basic operations: addition, subtraction, scalar multiplication
- Provides magnitude and normalization functions

#### `Point`
- Represents a physical point in 3D space
- Properties: position, velocity, initial velocity, acceleration, friction coefficient
- Method: `updatePosition(time)` - updates position using kinematic equation
- Method: `applyForce(force)` - applies external forces to the point

#### `Force`
- Represents a force with direction and magnitude range
- Properties: normalized direction vector, min/max magnitude
- Method: `generateForce()` - creates random force within magnitude range

#### `Simulator`
- Main simulation orchestrator
- Manages points, forces, and time evolution
- Handles random initialization of all simulation entities
- Supports both console output and VTK file generation

#### `VTKWriter`
- Handles VTK output for 3D visualization
- Creates individual `.vtp` files for each time step
- Generates `.pvd` collection files for temporal animation
- Includes all physics properties as visualization data

#### `ConfigParser`
- Parses configuration files for simulation parameters
- Supports both long names (`cube_size`) and short names (`L`)
- Handles comments and flexible formatting
- Validates file extensions (.cfg, .config, .conf)

### Data Flow

1. **Initialization**: Random placement of points within cube bounds
2. **Force Application**: Each point receives M randomly generated forces
3. **Time Evolution**: For each time step, update all point positions
4. **Output**: Console display and optional VTK file generation

## Build Requirements

- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.10 or higher
- VTK library (optional, for visualization output)

## Building the Project

### Using CMake (Recommended)

```bash
mkdir build
cd build
cmake ..
make
```

The executable will be created in the `run/` directory.

### Using Make

```bash
make
```

The executable will be created in the `run/` directory.

### Build Options

- **Release build**: `cmake -DCMAKE_BUILD_TYPE=Release ..`
- **Debug build**: `cmake -DCMAKE_BUILD_TYPE=Debug ..`
- **Without VTK**: The project will build without VTK if not found

## Usage

Zephyra supports two input modes:

### 1. Configuration File Mode (Recommended)

```bash
./run/3DPointSimulator <config_file>
```

Configuration files must have `.cfg`, `.config`, or `.conf` extension.

### 2. Command Line Parameter Mode

```bash
./run/3DPointSimulator <L> <N> <a1> <a2> <M> <amin> <amax> <vmin> <vmax> <v0min> <v0max> <T> [vtk_output_file]
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `L` | Cube side length (simulation bounds) |
| `N` | Number of points to simulate |
| `a1` | Minimum friction coefficient |
| `a2` | Maximum friction coefficient |
| `M` | Number of forces acting on each point |
| `amin` | Minimum acceleration value |
| `amax` | Maximum acceleration value |
| `vmin` | Minimum velocity value |
| `vmax` | Maximum velocity value |
| `v0min` | Minimum initial velocity value |
| `v0max` | Maximum initial velocity value |
| `T` | Simulation duration in seconds |
| `vtk_output_file` | Optional VTK output filename (without extension) |

## Configuration File Format

Configuration files use a simple key=value format with support for comments:

```ini
# 3D Physics Point Simulation Configuration File
# Lines starting with # are comments

# Basic simulation parameters
cube_size = 10.0              # Size of the simulation cube (L)
num_points = 5                # Number of points to simulate (N)

# Friction coefficient range
min_friction = 0.1            # Minimum friction coefficient (a1)
max_friction = 0.5            # Maximum friction coefficient (a2)

# Force parameters  
num_forces = 2                # Number of forces acting on each point (M)

# Acceleration range
min_acceleration = -2.0       # Minimum acceleration (amin)
max_acceleration = 2.0        # Maximum acceleration (amax)

# Velocity range
min_velocity = -1.0           # Minimum velocity (vmin)
max_velocity = 1.0            # Maximum velocity (vmax)

# Initial velocity range
min_initial_velocity = -0.5   # Minimum initial velocity (v0min)
max_initial_velocity = 0.5    # Maximum initial velocity (v0max)

# Time parameters
simulation_time = 10          # Simulation duration in seconds (T)

# VTK output (optional)
vtk_output_file = simulation_output
```

### Supported Parameter Names

Both long descriptive names and short mathematical names are supported:

| Long Name | Short Name | Description |
|-----------|------------|-------------|
| `cube_size` | `L` | Cube side length |
| `num_points` | `N` | Number of points |
| `min_friction` | `a1` | Minimum friction coefficient |
| `max_friction` | `a2` | Maximum friction coefficient |
| `num_forces` | `M` | Number of forces |
| `min_acceleration` | `amin` | Minimum acceleration |
| `max_acceleration` | `amax` | Maximum acceleration |
| `min_velocity` | `vmin` | Minimum velocity |
| `max_velocity` | `vmax` | Maximum velocity |
| `min_initial_velocity` | `v0min` | Minimum initial velocity |
| `max_initial_velocity` | `v0max` | Maximum initial velocity |
| `simulation_time` | `T` | Simulation duration |
| `vtk_output_file` | - | VTK output filename |

### Examples

#### Configuration File Mode
```bash
cd run
./3DPointSimulator simple_test.cfg
```

#### Basic Console Simulation
```bash
cd run
./3DPointSimulator 10.0 3 0.1 0.5 2 -2.0 2.0 -1.0 1.0 -0.5 0.5 5
```

#### Simulation with VTK Output
```bash
cd run
./3DPointSimulator 10.0 3 0.1 0.5 2 -2.0 2.0 -1.0 1.0 -0.5 0.5 5 simulation
```

### Quick Test Commands

```bash
# Build and run with simple config
mkdir build && cd build && cmake .. && make && cd ../run && ./3DPointSimulator simple_test.cfg
```

## VTK Visualization

When VTK output is enabled, the 3D Physics Point Simulator generates:

### Individual Time Step Files
- `filename_t0000.vtp` through `filename_tNNNN.vtp`
- Each contains point positions and physics properties for that time step
- Includes velocity vectors, acceleration vectors, and friction coefficients

### ParaView Collection File
- `filename.pvd` - Master file for temporal animation
- Open this file in ParaView to see the full time evolution
- Supports playback controls for time-based animation

### Visualization Data
- **Positions**: 3D coordinates of all points
- **Velocity**: Vector field showing motion direction and speed
- **Acceleration**: Vector field showing force effects
- **Friction**: Scalar field showing resistance coefficients

## Physics Implementation

### Motion Equation
The simulation implements the kinematic equation `s(t) = ½at² + vt + v₀` where:
- Position is updated each time step based on cumulative effects
- Friction is applied as a velocity-dependent force
- Multiple forces contribute to total acceleration

### Random Initialization
- Points: Uniformly distributed within cube bounds `[-L/2, L/2]³`
- Forces: Random direction vectors with random magnitudes
- Properties: All physics parameters randomly assigned within specified ranges

### Time Integration
- Discrete time steps of 1 second
- Position updates consider both initial velocity and accumulated acceleration
- Friction forces oppose motion direction

## File Structure

```
3DPointSimulator/
├── CMakeLists.txt          # CMake build configuration
├── README.md              # This documentation
├── Vector3D.h             # 3D vector mathematics
├── Point.h/.cpp           # Physical point representation
├── Force.h/.cpp           # Force system
├── Simulator.h/.cpp       # Main simulation engine
├── VTKWriter.h/.cpp       # VTK output functionality
├── ConfigParser.h/.cpp    # Configuration file parsing
├── main.cpp               # Command-line interface
├── example.cfg            # Example configuration file
└── run/                   # Executable output directory
    ├── simple_test.cfg    # Simple test configuration
    └── 3DPointSimulator   # Compiled executable (after build)
```

## Installation

```bash
cd build && make install
```

This installs the `3DPointSimulator` binary to `/usr/local/bin/`.

## Contributing

The codebase follows modern C++ practices:
- RAII resource management
- Clear separation of concerns
- Comprehensive error handling
- Consistent naming conventions

## Future Enhancements

Potential areas for expansion:
- Qt GUI for interactive parameter setting
- Multi-threading for performance optimization  
- Additional force types (gravitational, electromagnetic)
- Collision detection and response
- Advanced integration methods (Runge-Kutta)
- GUI interface for interactive configuration

## License

This project demonstrates 3D physics simulation concepts and VTK integration for educational and research purposes.