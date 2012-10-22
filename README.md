PTG
===

Procedural Terrain Generator

A library and an application for generating two dimensional heightmaps.
It's intention is to provide modular and useful abstractions for terrain generation.

Algorithms
----------

The following algorithms are implemented:
* Diamond Square (has a bug)

The following are in development:
* Midpoint Displacement
* Perlin Noise

This project was initiated as an assignment for an algorithms course at UNSW

Building (on *nixes)
--------------------
    git clone git://github.com/bobbaluba/PTG.git
    cd PTG
    mkdir build
    cd build
    cmake ../src
    make


Dependencies
------------

The library depends on the helsing utility library, which is developed alongside this project.
The helsing library currently depends on OpenGL 2.0, this is going to be fixed.

The viewer depends on OpenGL and SFML 2.

Much of the code uses c++11 functionality. The code should compile with g++ 4.7

License
-------

A GPL-like license will soon be provided.
