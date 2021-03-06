PTG                                    {#mainpage}
===

Procedural Terrain Generator

A library and an application for generating and viewing two dimensional heightmaps.
It's intention is to provide modular and useful abstractions for terrain heightmap generation.

The project was initiated as an assignment for an algorithms course at UNSW

Algorithms
----------

A description/analysis of each algorithm can be found in it's header file in include/ptg/<algorithm>.hpp

The following (major) algorithms are implemented:

**Recursive displacement algorithms:**
* Midpoint displacement
* Diamond square
* Modified diamond square (diamond square without the axis aligned ridges)
  ![screenshot of modified diamond square terrain](http://bobbaluba.github.com/PTG/screenshots/diamondsquare.png)

**Fractal noise algorithms:**
* Fractional brownian motion
* Ridged multifractal
  ![screenshot of ridged multifractal](http://bobbaluba.github.com/PTG/screenshots/ridgedmultifractal.png)
* Hybrid multifractal
  ![screenshot of hybrid multifractal](http://bobbaluba.github.com/PTG/screenshots/hybridmultifractal.png)

**Heightmap post-filters:**
* Gaussian blur
* Thermal erosion (uses a cellular automata)
  ![screenshot of thermal erosion](http://bobbaluba.github.com/PTG/screenshots/hybridmultifractaleroded.png)

**Pure 2D noise functions:**
* Perlin noise
* Value noise

Building
--------

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
It is meant as an example on how to use the library, as well as a way to get familiar with the different algorithms and their parameters.

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
* B: Toggle gaussian blur filter
* E: Toggle thermal erosion filter
* K/L: Adjust amplitude of terrain (just a scaling factor)
* N/M: Adjust gain. For fractal algorithms, this is the factor the amplitude is multiplied with each iteration.
* U/I: Adjust number of octaves for multifractal signals
* Z/X: Adjust offset for hybrid multifractal
* C/V: Adjust lacunarity for multifractal signals
* Comma/Period: Adjust H value (multifractal spectral value)
* F1/F2: Adjust thermal erosion iterations
* F3/F4: Adjust thermal erosion slope threshold
* 1-9: Algorithm seletion
    * 1: Midpoint Displacement
    * 2: Diamond-Square
    * 3: Helsing-square (my own modified version of diamond square)
    * 4: Pure perlin noise
    * 5: Fractional Brownian motion using perlin noise as input signal
    * 6: Pure value noise
    * 7: Fractional Brownian motion using value noise as input signal
    * 8: Hybrid Multifractal using perlin noise as input signal
    * 9: Ridged Multifractal using perlin noise as input signal

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

The code is available under the zlib license:
    
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
