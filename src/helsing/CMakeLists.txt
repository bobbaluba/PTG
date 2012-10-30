set(helsing_lib_src
	Application.cpp
	HeightMap.cpp
	MatrixStack.cpp
	Shader.cpp
	TextFile.cpp
)

add_library(helsing SHARED ${helsing_lib_src})
