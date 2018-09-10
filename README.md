# Installation #

1. Required packets

The project requires different packets related to OpenGL to be present inside of the system.

It is necessary to detain the library `freeglut` as well as its header files.
If those components are not already installed, they can be otabined using the apt-get command:
`sudo apt-get install freeglut3 freeglut3-dev`

In addition to the `freeglut` the project also requires the `glut` library.
This library can be installed using the following apt-get command:
`sudo apt-get install libglew1.6 libglew1.6-dev`

2. Compilation

If all the above mentioned librairies are part of the system, then it possible to proceed to the installation (compilation) of the game.
To do so, the user needs to be type-in `makefile` once within the root directory of the project.

# Usage #

Once compilation is done, the game can simply be launched by typing `./magnus_pong` while being within the project directory.

# Notes #

The project make use of SOIL (Simple OpenGL Image Library), a library that enables the loading of images (textures) in memory.
This library is built automatically during the compilation carried out by the makefile.

# Demo #

(Android version) Youtube demonstration: https://www.youtube.com/watch?v=ROjV22fV5MU


