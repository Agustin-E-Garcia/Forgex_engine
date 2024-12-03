# Forgex Engine
![Latest Release](https://img.shields.io/github/v/release/Agustin-E-Garcia/Forgex_engine?include_prereleases&label=release&link=)


A personal learning project exploring the creation of a voxel engine. This project demonstrates technical problem-solving, optimization techniques, and passion for game development. 

**Forgex Engine is an ongoing project, with new features and improvements being actively developed.**

## Table of Contents
1. [Features](#features)
2. [Performance](#performance)
3. [Libraries Used](#libraries-used)
4. [How to Build](#how-to-build)
5. [Goals](#goals)
   - [Short-Term Goals](#short-term-goals)
   - [Long-Term Goals](#long-term-goals)
6. [Images](#images)
7. [Status](#status)


## Features
- **Dynamic Chunk System:** Infinite world generation with 32x224x32 chunks, subdivided into 32x32x32 sub-chunks for optimal performance and memory management.
- **Binary Meshing:** Efficient meshing system to reduce geometry complexity, with boundary checks ensuring seamless transitions between sub-chunks.
- **Vertex Caching & Face Culling:** Minimizes computation by regenerating only modified chunks and skipping unseen faces for rendering.
- **Compact Memory Management:** Data stored efficiently using `uint32_t` for voxel grids and `uint8_t` for voxel types, ensuring minimal overhead.

## Performance
> Still gathering some data in terms of performance as I test in multiple computers when I have the chance. Will update soon with some example systems and the performance values for each

## Libraries Used
- **OpenGL:** Rendering
- **ImGui (Docking branch):** Engine UI and tools
- **GLM:** Math calculations
- **SPDlog:** Console logging
- **GLFW/GLEW:** Windowing and OpenGL extensions
- **STBImage:** Image loading

## Downloading the project
When enough features or changes have been added to the development branch, they will be merged to main and the release will be updated with a stable build

## How to Build
1. **Clone the Repository** Pull the latest version of the project
> **Note:** "Main" branch is a stable version of the engine that will compile and run, "Development" is an unstable branch where changes are being made often
2. **Generate Project Files** Use Premake5 to generate the project files
3. **Build the Project** Open the generated solution or Makefile and build it using your preferred IDE or build tool.
 > **Note:** A CMake option for generating project files may be added in the future.

## Goals
### Short-Term Goals
- Add a skybox with ambient light to enhance the world environment.
- Implement a project structure with asset handling
- Optimize chunk loading and meshing performance for smoother gameplay.
- Expand UI functionality using ImGui for better debugging and visualization.

### Long-Term Goals
- Add other voxel rendering techniques (raycasting, ray-marching, marching-cubes)
- Add advanced lighting and shadowing techniques to improve visuals.
- Introduce multiplayer support with synced voxel interactions.
- Create a demo scene showcasing infinite world generation and voxel editing.

## Images
![image](https://github.com/user-attachments/assets/88f2dc54-4418-4157-80f2-4367626892b6)


## Status
Forgex Engine is currently **a work in progress**, designed as a personal learning project and a showcase of technical skills. Contributions or forks are not expected, but feedback is always welcome!

---
