# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SFML_STATIC_LIBRARIES TRUE)

set(ptgview_src
	PTGView.cpp
	main.cpp
	Renderer.cpp
	Water.cpp
	TerrainMesh.cpp
)

add_executable(ptgview 
	${ptgview_src}
)

target_link_libraries(ptgview
	helsing
	ptg
        ${SFML_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARY}
)

