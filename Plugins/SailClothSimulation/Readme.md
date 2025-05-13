# SailClothSimulation Plugin

A GPU-based cloth and aerodynamic simulation system for Unreal Engine.

## Features:
- GPU-based cloth simulation using XPBD constraints.
- Vortex Lattice Method (VLM) for aerodynamic lift and drag calculations.
- Debug visualization for constraint errors, lift/drag vectors, and circulation.

## Directory Structure:
- **Shaders/** - Contains all compute shaders.
- **Source/** - C++ source files for component and shader dispatch.
- **SailClothSimulation.uplugin** - Plugin configuration file.

## Installation:
1. Copy the `SailClothSimulation` folder into your Unreal project `Plugins` directory.
2. Open the `.uproject` file and enable the `SailClothSimulation` plugin.
3. Build the project to compile shaders and source files.

## Usage:
- Add a `USailClothComponent` to any actor.
- Configure grid size, wind parameters, and simulation settings via Blueprints or C++.
