set(ptg_lib_src
	Continuous2DSignal.cpp
	Continuous2DSignalTerrain.cpp
	DiamondSquareTerrain.cpp
	FractionalBrownianMotion.cpp
	GaussianBlurTerrain.cpp
	HelsingSquareTerrain.cpp
	HybridFractal.cpp
	MidpointDisplacementTerrain.cpp
	PerlinNoise.cpp
	Seedable.cpp
	Terrain.cpp
	ValueNoise.cpp
)

add_library(ptg SHARED ${ptg_lib_src})
