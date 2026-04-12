# ARCADE

Welcome to our Arcade Project.

This document explains how to build, use, and extend the project.
For a complete overview of the architecture, refer to `schema_archi_arcade`.

## Build

To compile the project, use:

```bash
make
```

Available rules:

```bash
make        # build everything
make re     # rebuild everything
make clean  # remove object files
make fclean # remove binaries and object files
```



## Overview

The Core is responsible for managing two dynamic libraries at runtime:

- one graphical module (display)
- one game module

It handles the main loop by:
- sending ```ArcadeEvents``` to the game module
- retrieving ```GameData``` from the game
- passing the data to the display module for rendering



## Adding a Graphical Library

### 1. Implement ```IDisplayModule```

Create a class that publicly inherits from ```IDisplayModule```.

### 2. Expose required entry points

Your shared library (```.so```) must export the following symbols:

- ```getInstance```: returns a pointer to your display module instance
- ```getType```: returns a ```LibType```

### 3. Implement rendering

You must implement:

```bash
draw(GameData data)
```

Where ```GameData``` contains:

- ```data.bitmap```  
  A ```std::map<std::pair<size_t, size_t>, ACube>``` representing the game grid

- ```data.text```  
  A ```std::vector<ArcadeText>``` used for HUD elements (score, labels, etc.)

- ```data.GameOver```  
  A boolean indicating whether the game has ended

### 4. Build the library

Compile your module as a shared library (```.so```) and place it in:

```bash
./lib/
```

The ```DLLoader``` will automatically detect and load it.



## Adding a Game

### 1. Implement ```IGameModule```

Create a class that publicly inherits from ```IGameModule```.

### 2. Expose required entry points

Your shared library (```.so```) must export:

- ```getInstance```: returns a pointer to your game instance
- ```getType```: returns a ```LibType```

### 3. Handle events

The ```update()``` function is called every frame with the latest ```ArcadeEvents```.

You must:
- process input events
- update your game state accordingly

### 4. Provide game data

Implement:

```bash
getGameData()
```

This function must return a ```GameData``` structure used by the display module.

### 5. Build the library

Compile your game as a shared library (```.so```) and place it in:

```bash
./lib/
```



## Important

Make sure all your libraries are placed in the ```./lib/``` directory so they can be loaded dynamically.

For full technical details and architecture diagrams, refer to:

```
schema_archi_arcade
```
