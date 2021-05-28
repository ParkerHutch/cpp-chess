## Prerequisites
1. Install CMake
2. Install the 'CMake' and 'CMake Tools' extensions in VSCode
3. In the extension settings for 'CMake Tools', set the 'Generator' to be 'MinGW Makefiles'.

## Setting up
1. Compile SFML and CMake (see guide online / other info on here)
2. Copy CMakeLists.txt into the project you want to use SFML with
3. Modify variables in CMakeLists.txt, like the main cpp file, etc.
4. In VSCode, ctrl+shift+P->Cmake:Configure->Select proper compiler
5. Build file should be created by step 4, paste the dll files from the SFML bin folder in there
- If your code compiles correctly but doesn't run, it could be because the dll
files are not present with the executable
6. Click the "Build" and "Run" buttons at the bottom of the screen in VSCode to
build and run the file
- If Build doesn't work, try running cmake -G"MinGW Makefiles" . first

## Resources
These guides may be helpful:
- https://github.com/SFML/SFML/wiki/Tutorial%3A-Build-your-SFML-project-with-CMake
- https://www.sfml-dev.org/tutorials/2.5/start-linux.php
