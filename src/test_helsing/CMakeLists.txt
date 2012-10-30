# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(test_hmath
	test_hmath.cpp
)

add_executable(test_Application
	test_Application.cpp
)

add_executable(test_Shader
	test_Shader.cpp
)

target_link_libraries(test_hmath
	helsing
)

target_link_libraries(test_Application
	helsing
        ${SFML_LIBRARIES}
        ${GLEW_LIBRARY}
)

target_link_libraries(test_Shader
	helsing
        ${SFML_LIBRARIES}
        ${GLEW_LIBRARY}
)
