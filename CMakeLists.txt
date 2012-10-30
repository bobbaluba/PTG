cmake_minimum_required (VERSION 2.6)
project (PTG)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall")
ADD_DEFINITIONS("-std=c++0x")

message(${PROJECT_SOURCE_DIR})

#configure a header file to pass some of the CMake settings to the source code
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

#add the binary tree to the search path for include files so that we will find config.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")

#add cmake_modules to the CMAKE_MODULES_PATH
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#detect and add SFML
find_package(SFML 2.0 REQUIRED system window graphics)

#detect glew
find_package(GLEW REQUIRED)

#build libraries
add_subdirectory("${PROJECT_SOURCE_DIR}/src/helsing")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/ptg")

#output the binary to the root of the build directory
add_subdirectory("${PROJECT_SOURCE_DIR}/src/ptgview" "ptgview") 

#what's this? ghost code... ?
#CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
include(CPack)
