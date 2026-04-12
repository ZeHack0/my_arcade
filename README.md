# Arcade
Retro gaming platform developed in C++ using dynamic libraries.

## Description
Arcade is a modular gaming platform that allows users to play multiple retro games with different graphical libraries, loaded dynamically at runtime.</br>
The project is built around a core executable that loads both game modules and graphical libraries as shared objects (```.so```), ensuring flexibility and extensibility.

## Features
- Dynamic loading of games and graphical libraries (```dlopen```, ```dlsym```, ```dlclose```)
- Runtime switching between graphical libraries
- Multiple games support
- Score system
- User name input
- Modular architecture (plug-in system)

## Implemented Games
- Snake
- Centipede

## Implemented Graphical Libraries
- ncurses
- SDL2
- SFML

## Requirements
- C++ compiler (g++)
- Make
- Linux environment
- Required libraries:
  - ncurses
  - SDL2
  - SFML

## Build
### Using Makefile
    make
#### Other available rules:
    make core        # build only the core
    make games       # build game libraries
    make graphicals  # build graphical libraries
    make clean
    make fclean
    make re

### Usage
    ./arcade ./lib/arcade_ncurses.so

## Controls
- Switch graphical library
- Switch game
- Restart game
- Return to menu
- Exit program

## Project Structure
    .
    ├── arcade              # core executable
    ├── lib/
    │   ├── arcade_ncurses.so
    │   ├── arcade_sdl2.so
    │   ├── arcade_sfml.so
    │   ├── arcade_snake.so
    │   └── arcade_centipede.so
    ├── src/
    ├── include/
    ├── Makefile
    └── README.md

## Architecture
The project follows a strict separation:
- Core:
  - Handles dynamic loading
  - Manages menus, scores, and user input
- Graphical libraries:
  - Handle rendering and input
- Game libraries:
  - Handle game logic only

No graphical dependency is allowed in the core or game logic.

## Error Handling
- Errors are printed to stderr
- Program exits with code 84 on failure

## Extending the Project
To add a new game or graphical library:
1. Implement the required interface
2. Compile it as a shared library (```.so```)
3. Place it in the ```./lib/``` directory

The core will automatically detect and load it.

## Documentation
Additional documentation is available in the ```./doc/``` directory, including:
- How to implement new libraries
- Architecture overview

## Collaboration
Interface shared with another group as required by the subject.

## Authors
- Ronan BOTREL | [Github](https://github.com/ZeHack0)
- Thibaut HIEN | [Github](https://github.com/tibote)
- Titouan MENORET | [Github](https://github.com/titouan-mnt)