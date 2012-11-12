set(ptg_lib_src
	Continuous2DSignal.cpp
	Continuous2DSignalTerrain.cpp
	DiamondSquareTerrain.cpp
	FractionalBrownianMotion.cpp
	GaussianBlurTerrain.cpp
	HelsingSquareTerrain.cpp
	HybridMultiFractal.cpp
	MidpointDisplacementTerrain.cpp
	PerlinNoise.cpp
	RidgedMultiFractal.cpp
	Seedable.cpp
	Terrain.cpp
	ThermalErosionTerrain.cpp
	ValueNoise.cpp
)

add_library(ptg SHARED ${ptg_lib_src})
