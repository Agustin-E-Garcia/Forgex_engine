# Forgex Engine
![Latest Release](https://img.shields.io/github/v/release/Agustin-E-Garcia/Forgex_engine?include_prereleases&label=release&link=)
[![Build Status](https://github.com/Agustin-E-Garcia/Forgex_engine/actions/workflows/BuildStatus.yml/badge.svg)](https://github.com/Agustin-E-Garcia/Forgex_engine/actions/workflows/BuildStatus.yml)


A personal learning project exploring the creation of a destructible voxel engine, built from scratch in C++.

**Forgex Engine is an ongoing project, with new features and improvements being actively developed.**

## Table of Contents
1. [Overview](#overview)
2. [Features](#features)
3. [Libraries Used](#libraries-used)
4. [How to Build](#how-to-build)
5. [Goals](#goals)
   - [Short-Term Goals](#short-term-goals)
   - [Long-Term Goals](#long-term-goals)
8. [Status](#status)

## Overview
Forgex is a C++ game engine designed around fully destructible voxel environments, targeting small to medium bounded arenas. The engine uses Marching Cubes for smooth isosurface mesh generation from a scalar density field, with the objective of making destruction feel organic, surfaces deform and crumble rather than disappearing in discrete blocks.
The long-term goal is to ship a singleplayer horror demo built on top of this engine, where light and darkness are core gameplay mechanics in a fully destructible environment.

## Features
- **Modular Architecture:** Engine functionality split into independently compiled libraries (Core, Graphics, Scene, Voxel, Debug, Assets), linked into a single executable
- **Entity Component System:** Built on EnTT, with a clean separation between update systems and render systems
Marching Cubes Terrain: Smooth voxel mesh generation from a scalar density field using Simplex Brownian Motion noise, with flat shading for a low-poly aesthetic
- **Chunk System:** Terrain divided into 64x64x64 chunks, each independently generated and meshable for future destruction support
- **Asset Manager:** Centralized asset loading and management with path-based deduplication
- **Debug Tooling:** In-engine developer console (F1) with command system, system profiler, entity inspector, and asset inspector

## Libraries Used
- **OpenGL:** Rendering
- **ImGui (Docking branch):** Engine UI and tools
- **EnTT:** Entity Component System
- **GLM:** Math calculations
- **SPDlog:** Console logging
- **GLFW/GLEW:** Windowing and OpenGL extensions
- **STBImage:** Image loading
- **NoiseFastLite** Noise generation

## How to Build
1. **Clone the Repository** Pull the latest version of the project
2. **Generate Build Files** Generate build files using CMake
3. **Build the Project** Build the project
   > **Note:** "Main" branch is a stable version of the engine that will compile and run, "Development" is an unstable branch where changes are being made often

## Goals
### Short-Term Goals
- Terrain destruction modifying the density field at runtime and remeshing affected chunks
- Forward rendering lighting system with dynamic point lights
- Mesh loading and rendering with AssetHandles using the AssetManager

### Long-Term Goals
- Render thread and chunk generation thread for multithreaded architecture
- Game DLL loading — separate game code from engine runtime
- Singleplayer horror demo built on top of the engine

## Status
Forgex Engine is currently **a work in progress**, designed as a personal learning project and a showcase of technical skills. Contributions or forks are not expected, but feedback is always welcome!

---
