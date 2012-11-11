PTG                                    {#mainpage}
===

Procedural Terrain Generator

![screenshot](http://bobbaluba.github.com/PTG/screenshots/diamondsquare.png)

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
* Gaussian Blur (decorates other terrains)

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

The viewer
----------------

A viewer, ptgview, is provided for viewing generated terrains.

The viewer accepts the following command line options:

-h, --help
    View help and available command line arguments.

-f, --fullscreen
    Run the application in fullscreen using the current resolution of the desktop.

**Navigating the viewer:**

* A/D: Move left/right
* W/S: Move forward/backward
* Left Mouse button: Toggle viewing mode (flying or centered)
* Space/Return/Right Mouse button: Reseed the terrains
* R/F: Move up/down
* T/G: Raise/Lower water
* O/P: Adjust terrain detail
* K/L: Adjust amplitude of terrain (just a scaling factor)
* N/M: Adjust gain. For fractal algorithms, this is the factor the amplitude is multiplied with each iteration.
* U/I: Adjust number of octaves for fractional brownian motion signal
* 1-4: Algorithm seletion
    * 1: Midpoint Displacement
    * 2: Diamond-Square
    * 3: Helsing-square (my own modified version of diamond square)
    * 4: Pure perlin noise
    * 5: Fractional Brownian motion using perlin noise as input signal
    * 4: Pure value noise
    * 5: Fractional Brownian motion using value noise as input signal

Documentation
-------------

[Documentation for the API](http://bobbaluba.github.com/PTG/docs/html)

Documentation for the library can be found in the header files in the include/ptg
directory.

You can also compile the documentation using doxygen to get a pdf or an html site.
To compile the documentation run

    cd PTG
    sudo apt-get install doxygen
    doxygen

Or similar, the documentation will appear in PTG/docs/html/

License
-------
PTG - Copyright (c) 2012 Johan Klokkhammer Helsing - johanhelsing@gmail.com

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
