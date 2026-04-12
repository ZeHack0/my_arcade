ARCADE

Welcome to our Arcade Project here's how to use it:
! DONT FORGET TO CHECK schema_archi_arcade for every technical detail.

To compile, use make, make re/clean/fclean

The Core manages two dynamic libraries at a time: one display module and one game module. It drives the main loop, pipes ArcadeEvents into the game, retrieves GameData, and hands it to the display.

Adding a Graphic Library
1. Implement IDisplayModule
Create a class that publicly inherits from IDisplayModule

2. Expose the mandatory C entry point
Your .so must export:
    - the symbol getInstance wich return a pointer of the class
    - the symbol getType wich return a LibType

3. Implement rendering from GameData
draw(GameData data) receives:

data.bitmap — a std::map<std::pair<size_t,size_t>, ACube> representing the game grid.
data.text — a std::vector<ArcadeText> for HUD / score labels.
data.GameOver — true when the game has ended.

4. Build a shared library
Place the resulting .so alongside the other libraries inside the ./lib folder so DLLoader can find it.

Adding a Game

1. Implement IGameModule
Create a class that publicly inherits from IGameModule.

2. Expose the mandatory C entry point
Your .so must export:
    - the symbol getInstance wich return a pointer of the class
    - the symbol getType wich return a LibType

3. Handle ArcadeEvents
update() is called every frame with the latest ArcadeEvents. Determine the actions in your game in the case of the given event.

4. Return GameData

Use the getGameData() method to return a gameData structure used to display game.

5. Build a shared library
Place the resulting .so alongside the other libraries inside the ./lib folder so DLLoader can find it.



DONT FORGET TO CHECK schema_archi_arcade for every technical detail.