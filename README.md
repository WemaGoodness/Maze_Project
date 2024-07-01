# Maze Game Project

## Description

This project is a 3D maze game implemented using SDL2. The game involves navigating a player through a maze, avoiding or confronting enemies, and experiencing dynamic weather effects such as rain.

## Controls

- **W**: Move forward
- **A**: Move left
- **S**: Move backward
- **D**: Move right
- **Mouse**: Look around
- **Shift**: Hold to move twice as fast
- **M**: Toggle the full-screen map on/off
- **Escape**: Quit the game

## Features

- **Raycasting**: The game uses a raycasting technique to render the 3D maze.
- **Enemies**: Simple AI enemies that follow the player.
- **Weather Effects**: Dynamic rain particles enhance the game environment.

## Installation

To compile the game, ensure you have `SDL2` installed. Then run:

```bash
make

## Running the game

To run the game, use:

```bash
./maze_game <path_to_map_file>

Example:

```bash
./maze_game map.txt
