# Meowstuck
A small 2D tile based RPG. Probably.

## How to compile (on Linux)

1. Install the 2D library [SFML](https://www.sfml-dev.org/). If you're using Linux, check if your distribution has
   a prebuilt package for SFML (e.g. `community/sfml` on Arch Linux or `libsfml-dev` on Ubuntu/Debian).
   
2. Clone the repository:
   ```
   git clone https://github.com/binaryDiv/meowstuck.git
   ```
   
3. By default the Makefile uses `clang++` as the C++ compiler. If you don't have clang installed, just change the `CXX` variable
   in the Makefile to use gcc's `g++` instead (should be one of the first lines):
   ```
   CXX := g++
   ```
   
4. Compile!
   ```
   make
   ```
   
5. If it compiled successfully, you're done! To run the game, stay in the repository's root directory and run:
   ```
   ./bin/meowstuck
   # alternatively:
   make run
   ```

If you have any problems, feel free to contact [me](https://twitter.com/binaryDiv).

## How to compile (on Windows and others systems)

For now, you have to figure out yourself how to compile on Windows or any other system, sorry. :(

If you want a prebuilt Windows executable, just ask me and I'll try to build one.
