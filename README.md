PTG
===

Procedural Terrain Generator

A library and an application for generating and viewing two dimensional heightmaps.
It's intention is to provide modular and useful abstractions for terrain generation.

The project is at an early stage. Builds and interfaces will break all the time.

The project was initiated as an assignment for an algorithms course at UNSW

Algorithms
----------

The following algorithms are implemented:
* Midpoint Displacement
* Diamond Square
* Fractional Brownian Motion

Noise functions:
* Perlin Noise

Additional algorithms in development:
* Value noise

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

License
-------

A GPL-like license will soon be provided.
