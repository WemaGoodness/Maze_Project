# 3D Maze Game Project

## Table of Contents
	1. [Description](#description)
	2. [Controls](#controls)
	3. [Features](#features)
	4. [Non-Deployed Actions](#non-deployed-actions)
	5. [Installation](#installation)
	6. [Running the Game](#running-the-game)
	7. [Resources](#resources)
	8. [References](#references)
9. [Landing Page](#landing-page)

## Description

	This project is a 3D maze game implemented using SDL2. The game involves navigating a player through a maze, avoiding or confronting enemies, and experiencing dynamic weather effects such as rain.

## Controls

	- **W**: Move forward
	- **A**: Move left
	- **S**: Move backward
	- **D**: Move right
	- **Right Arrow**: Strafe camera right
	- **Left Arrow**: Strafe camera left
	- **Shift**: Hold to move twice as fast
	- **Escape**: Quit the game

## Features

	- **Raycasting**: The game uses a raycasting technique to render the 3D maze.
	- **Enemies**: Simple AI enemies that follow the player.
	- **Weather Effects**: Dynamic rain particles enhance the game environment.

## Non-Deployed Actions

	The following features are currently not deployed:

	- Weather change
	- Strafing camera up or down
	- Enemies
	- Weapons
	- Loading of external textures using images

## Installation

	To compile the game, ensure you have `SDL2` installed. Then run:

	```bash
	make all

## Running The Game

	To run the game use:

	```bash
	./maze

## Resources

	To install SDL2 resources on different platforms, follow the instructions below:

	Linux Terminal:
	```bash
	sudo apt-get install libsdl2-dev
	sudo apt-get install libsdl2-image-dev

	Windows:
	Download the SDL2 development libraries from the SDL website, and follow the instructions provided in the downloaded package.

	Mac:
	```bash
	brew install sdl2
	brew install sdl2_image


