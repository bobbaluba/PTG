PTG
===

Procedural Terrain Generator

A library and an application for generating and viewing two dimensional heightmaps.
It's intention is to provide modular and useful abstractions for terrain generation.

The project is at an early stage. Builds and interfaces will break all the time.

The project was initiated as an assignment for an algorithms course at UNSW

Algorithms
----------

The following (major) algorithms are implemented:

Terrain algorithms:
* Midpoint Displacement
* Diamond Square
* Fractional Brownian Motion

Noise functions:
* Perlin Noise

Additional algorithms in development:
* Value noise
* Erosion filter

Building
--------

The library depends on the helsing utility library, which is developed alongside this project.
The helsing library currently depends on OpenGL 2.0, this is going to be fixed.

The viewer depends on OpenGL and SFML 2.

Much of the code uses c++11 functionality. The code should compile with g++ 4.7+

To build project on *nix, run the following:

    git clone git://github.com/bobbaluba/PTG.git
    cd PTG
    mkdir build
    cd build
    cmake ..
    make

Using the viewer
----------------

A viewer, ptgview, is provided for viewing generated terrains.

The viewer accepts the following command line options:

-h, --help
    View help and available command line arguments.

-f, --fullscreen
    Run the application in fullscreen using the current resolution of the desktop.

===Navigating the viewer===

* A/D: Move left/right
* W/S: Move forward/backward
* Left Mouse button: Toggle viewing mode (flying or centered)
* Right Mouse button: Reseed the terrains
* R/F: Move up/down
* U/J: Raise/Lower water
* O/P: Adjust terrain detail
* K/L: Adjust amplitude of terrain (just a scaling factor)
* N/M: Adjust gain. For fractal algorithms, this is the factor the amplitude is multiplied with each iteration.
* 1-4: Algorithm seletion
    * 1: Diamond-Square
    * 2: Midpoint Displacement
    * 3: Pure perlin noise
    * 4: Fractional Brownian motion using perlin noise as input signal


License
-------

A GPL-like license will soon be provided.
