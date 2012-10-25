cmake_minimum_required (VERSION 2.6)
project (PTG)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

find_package(OpenGL)

set(CMAKE_CXX_FLAGS "-g -Wall")
ADD_DEFINITIONS("-std=c++0x")

message(${PROJECT_SOURCE_DIR})

#configure a header file to pass some of the CMake settings to the source code
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

#add the binary tree to the search path for include files so that wewill find config.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/../include")
include_directories("${PROJECT_SOURCE_DIR}")


#Add the src
# Define sources and executable
set(EXECUTABLE_NAME "terrainViewer")
add_executable(${EXECUTABLE_NAME}
	main.cpp
	LandscapeApplication.cpp
	Renderer.cpp
	QuadTree.cpp
	helsing/HeightMap.cpp
	helsing/MatrixStack.cpp
	helsing/TextFile.cpp
	helsing/Shader.cpp
	helsing/Movable.cpp
	helsing/Application.cpp
	Actor.cpp
	Water.cpp
	HeightMapActor.cpp
	Scene.cpp
	BasicScene.cpp
	SceneApplication.cpp
	Seedable.cpp
	Continuous2DSignal.cpp
	PerlinNoise.cpp
	Terrain.cpp
	MidpointDisplacementTerrain.cpp
	DiamondSquareTerrain.cpp
)
add_executable("test_hmath"
	test_helsing/test_hmath.cpp
)
add_executable("test_Application"
	test_helsing/test_Application.cpp
	helsing/Application.cpp
)
add_executable("test_Shader"
	test_helsing/test_Shader.cpp
	helsing/Shader.cpp
	helsing/Application.cpp
)
include_directories(${CMAKE_SOURCE_DIR}/../include)

#detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.0 REQUIRED system window graphics)
#detect glew
find_package(GLEW REQUIRED)

target_link_libraries(${EXECUTABLE_NAME} 
	${EXTRA_LIBS}
	${SFML_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARY}
)
target_link_libraries(test_Application
	${GLEW_LIBRARY}
	${SFML_LIBRARIES}
)
target_link_libraries(test_Shader
	${SFML_LIBRARIES}
	${GLEW_LIBRARY}
)

#add the install targets
install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)


#CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/../COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
include(CPack)
