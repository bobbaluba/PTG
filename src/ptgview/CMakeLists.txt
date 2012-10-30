# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(ptgview_src
	Actor.cpp
	BasicScene.cpp
	HeightMapActor.cpp
	LandscapeApplication.cpp
	main.cpp
	Renderer.cpp
	SceneApplication.cpp
	Scene.cpp
	Water.cpp
)

add_executable(ptgview 
	${ptgview_src}
)

target_link_libraries(ptgview
	helsing
	ptg
        ${EXTRA_LIBS} #what's this?
        ${SFML_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARY}
)

