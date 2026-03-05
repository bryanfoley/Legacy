# 2D Granular Compression Simulation (Legacy C Code)

## Overview

This repository contains a legacy C implementation of a **2D Discrete Element Method (DEM) granular simulation**, originally developed in 2013 using Eclipse CDT. The simulation models the compression of a polydisperse assembly of circular particles confined between rigid walls, tracking particle dynamics as the top wall is slowly pushed downward.

The main scientific goal is to characterise how macroscopic quantities such as the **packing density**, **coordination number**, **kinetic energy**, and **potential energy** evolve as the granular assembly is compressed toward the random-close-packing limit.

---

## Physics

The simulation is non-dimensionalised and uses a **linear spring–dashpot contact model**:

- **Contact force** between overlapping particles *i* and *j*:
  `F = (kn * δ - γ * m_red * v_rel·n̂) * n̂`
  where `δ` is the overlap, `kn` is the normal spring constant, `γ` is the dissipation constant, `m_red` is the reduced mass, and `n̂` is the unit normal.
- **Velocity Verlet integration** advances positions and velocities at each timestep `dt`.
- **Image particles** are used to handle periodic/boundary conditions near the walls.
- The **top wall** translates downward at constant speed `wall_speed` whenever the total kinetic energy drops below `max_energy`, compressing the assembly step by step.

Key simulation parameters (all defined in `incl/defines.h`):

| Parameter       | Value        | Description                                   |
|-----------------|--------------|-----------------------------------------------|
| `n_max`         | 100          | Number of free (mobile) particles             |
| `dt`            | 1e-3         | Integration time step                         |
| `kn`            | 1.0          | Normal spring constant                        |
| `gamma`         | 1.0          | Dissipation constant                          |
| `wall_speed`    | -1e-3        | Downward speed of the compressing wall        |
| `max_energy`    | 1e-4         | Kinetic energy threshold for wall translation |
| `min_packing`   | 0.00         | Starting packing density                      |
| `max_packing`   | 0.96         | Target maximum packing density                |

A `DEBUG_ON` preprocessor flag is defined in `incl/defines.h` and makes the simulation run with a smaller system and larger timestep for quick testing.

---

## Project Structure

```
.
├── Compress.c               # Main program (entry point)
├── makefile                 # GNU Make build file
├── config1.dat              # Input: initial (x, y) positions for 100 particles
├── incl/                    # Internal header files
│   ├── BFOL.h               # Custom type definitions (vectors, particles)
│   ├── defines.h            # Compile-time simulation parameters
│   ├── errorCodes.h         # ERR_MSG return-code enum
│   ├── files.h              # File handle declarations and fopen() calls
│   ├── includes.h           # Master include for all intf/ function headers
│   └── macros.h             # Macro definitions (reserved for expansion)
├── intf/                    # Function implementations (bodies in .h files)
│   ├── assign_image.h       # Assign image particles at periodic boundaries
│   ├── attain_positions.h   # Read particle positions
│   ├── average_velocity_x.h # Average x-velocity calculation
│   ├── average_velocity_y.h # Average y-velocity calculation
│   ├── bnd_check.h          # Boundary condition check
│   ├── calculate.h          # Pairwise force calculation (contact detection)
│   ├── coordination_number.h# Mean coordination number
│   ├── grain.h              # Grain utility functions
│   ├── initiate.h           # Initialise all arrays to zero
│   ├── kinetic.h            # Total kinetic energy
│   ├── macros.h             # Interface-level macros
│   ├── new_acc.h            # Update accelerations (Velocity Verlet step 2)
│   ├── new_pos.h            # Update positions (Velocity Verlet step 1)
│   ├── new_vel.h            # Update velocities (Velocity Verlet step 3)
│   ├── old_acc.h            # Store previous accelerations
│   ├── packing_density.h    # 2D packing density calculation
│   ├── potential.h          # Total potential energy
│   ├── print.h              # Write particle positions to file
│   ├── print_chains.h       # Print force-chain data
│   ├── reset_velocities.h   # Reset velocity arrays
│   ├── set_free_mass.h      # Set mass for free particles
│   ├── set_free_positions.h # Read initial positions from config1.dat
│   ├── set_free_radii.h     # Assign Gaussian-distributed radii to free particles
│   ├── set_free_velocities.h# Initialise free particle velocities
│   ├── set_static_mass.h    # Set mass for wall particles
│   ├── set_static_positions.h# Place wall particles on bottom/top rows
│   ├── set_static_radii.h   # Set radius for wall particles
│   ├── sum_forces.h         # Sum all forces on each free particle
│   ├── trace.h              # Tracing/logging utilities
│   ├── translate_wall.h     # Move the top wall downward
│   └── update.h             # Update old → new phase arrays
├── src/                     # Standalone C source files (compiled separately)
│   ├── set_free_mass.c      # Mass assignment for free particles
│   ├── set_free_radii.c     # Radius assignment for free particles
│   ├── set_static_mass.c    # Mass assignment for wall particles
│   └── set_static_radii.c   # Radius assignment for wall particles
├── results/                 # Output directory (must exist before running)
│   ├── positions.dat        # Free particle (x, y) positions over time
│   ├── velocities.dat       # Free particle velocities over time
│   ├── sys_props.dat        # System properties (masses, average radius)
│   ├── kinetic.dat          # Kinetic energy vs. time
│   ├── potential.dat        # Potential energy vs. packing density
│   ├── energy.dat           # Total energy vs. time
│   ├── radii.dat            # Free particle radii
│   ├── wall_positions.dat   # Wall particle positions
│   ├── image_positions.dat  # Image particle positions
│   ├── coordination_number.dat # Coordination number vs. packing density
│   ├── average_velocity.dat # Average velocity vs. time
│   └── trace                # Function call trace log (when TRACE_ON is defined)
├── results01.gz             # Archived results (run 1)
├── results02.gz             # Archived results (run 2)
├── Documentation.pdf        # Original project documentation
└── thesis.pdf               # Associated thesis document
```

> **Note on code structure:** This code uses an unusual C style where function bodies are placed inside `.h` header files and `#include` directives appear inside the `main()` function body. This was an Eclipse CDT convention used during development. The `src/` directory also contains `.c` files with function bodies, but these are not compiled separately — they are superseded by the `.h` implementations in `intf/`.

---

## Dependencies

The simulation depends only on the **C standard library** (C89/C90 compatible):

| Library   | Header       | Usage                              |
|-----------|--------------|------------------------------------|
| libc      | `stdio.h`    | File I/O (`printf`, `fopen`, etc.) |
| libc      | `stdlib.h`   | `rand()`, `malloc()`               |
| libm      | `math.h`     | `sqrt()`, `pow()`, `fabs()`, etc.  |
| libc      | `string.h`   | String utilities                   |
| libc      | `float.h`    | Floating-point limits              |
| libc      | `time.h`     | Timestamps (used by trace logging) |

**Build tools required:**

| Tool  | Minimum Version | Purpose          |
|-------|-----------------|------------------|
| `gcc` | Any modern      | C compiler       |
| `make`| Any modern      | Build automation |

No third-party libraries are needed.

---

## Building

Clone the repository and build from the repository root:

```bash
git clone https://github.com/bryanfoley/Legacy.git
cd Legacy
make
```

This compiles `Compress.c` into the `Compress` executable using:

```bash
gcc -c Compress.c -lm -w
gcc -o Compress Compress.o -lm -w
```

The `-lm` flag links the math library; `-w` suppresses compiler warnings (the code pre-dates modern C standards).

To **clean** build artifacts:

```bash
make clean
```

---

## Running

The simulation **must be run from the repository root** so that it can locate `config1.dat` (input) and write into the `results/` directory (output):

```bash
./Compress
```

Or equivalently:

```bash
make run
```

Expected console output (abbreviated):

```
Opening the output files
Done initialising!
Initialising
Assigning
Setting free particle radii
Setting free particle masses
Setting static particle mass
Setting static particle positions
Setting free particle positions
Initiating boundary check
Assigning Images
...
Packing Density = 0.010000
...
End of loop
```

The simulation writes results to the `results/` directory as it runs. The full run (with default parameters) is computationally intensive; the debug mode (see below) is recommended for quick testing.

---

## Configuration

### Input file — `config1.dat`

Contains the initial (x, y) positions for all 100 free particles, one particle per line with tab-separated coordinates:

```
5.850093    14.396191
1.741081    25.768303
...
```

### Compile-time parameters — `incl/defines.h`

Simulation behaviour is controlled entirely via `#define` macros. Edit `incl/defines.h` before building to change parameters.

#### Debug / quick-test mode

`DEBUG_ON` is enabled by default (see `incl/defines.h`). In debug mode:

| Parameter    | Normal value | Debug value | Effect                     |
|--------------|-------------|-------------|----------------------------|
| `dt`         | 1e-3        | 1e-1        | Larger timestep            |
| `t_max`      | 3000.0      | 3.0         | Much shorter run time      |
| `wall_step`  | 0.00001     | 0.001       | Faster wall compression    |
| `max_packing`| 0.96        | 0.40        | Lower target packing       |

To disable debug mode and run the full production simulation, comment out `#define DEBUG_ON` in `incl/defines.h`:

```c
/* #define DEBUG_ON */
```

---

## Output Files

All output is written to the `results/` directory:

| File                     | Contents                                              |
|--------------------------|-------------------------------------------------------|
| `positions.dat`          | Free particle (x, y) positions at each print step    |
| `velocities.dat`         | Free particle velocities at each print step           |
| `sys_props.dat`          | System properties: masses, average radius             |
| `kinetic.dat`            | Total kinetic energy over time                        |
| `potential.dat`          | Potential energy vs. packing density                  |
| `energy.dat`             | Total energy over time                                |
| `radii.dat`              | Free particle radii (Gaussian distributed)            |
| `wall_positions.dat`     | Wall particle positions                               |
| `image_positions.dat`    | Image particle positions                              |
| `coordination_number.dat`| Average coordination number vs. packing density       |
| `average_velocity.dat`   | Average particle velocity vs. time                    |
| `trace`                  | Function call trace log (only when `TRACE_ON` active) |

---

## Docker

A `Dockerfile` is provided to build and run the simulation in an isolated environment without needing to install any tools locally.

### Build the Docker image

```bash
docker build -t granular-sim .
```

### Run the simulation

```bash
docker run --rm -v "$(pwd)/results:/app/results" granular-sim
```

This mounts your local `results/` directory into the container so the output files are written to your host machine.

### Build and run in one step (for quick testing)

```bash
docker build -t granular-sim . && docker run --rm -v "$(pwd)/results:/app/results" granular-sim
```

---

## Known Limitations

- The main simulation loop is guarded by `if(ERR_OK == r)` where `r` is hardcoded to `ERR_NOK`, so the compression loop does **not** execute in the current code. The initialisation, force calculation, and single-step output still run successfully.
- The `src/*.c` files are not compiled by the makefile; their functionality is provided by the `intf/*.h` implementations included directly into `Compress.c`.
- Function bodies defined in `.h` files is non-standard; the `-w` compiler flag suppresses the resulting warnings.
- `void main(void)` is used instead of `int main(void)` — this is valid in older C standards but not C99/C11.
