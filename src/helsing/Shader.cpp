/**
 * @file Shader.cpp
 * @date 12. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <helsing/Shader.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>

namespace helsing {

Shader::Shader(const std::string vertexShader, const std::string fragmentShader) {
	hVertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* szVertex = vertexShader.c_str();
	glShaderSource(hVertexShader, 1, &szVertex, NULL);
	glCompileShader(hVertexShader);

	//check for compilation errors
	GLint compile;
	glGetShaderiv(hVertexShader, GL_COMPILE_STATUS, &compile);
	if(compile==GL_FALSE){
		std::cerr << "Vertex shader compilation failed\n";
		char szInfoLog[1024];
		glGetShaderInfoLog(hVertexShader, 1024, NULL, szInfoLog);
		std::cerr << "Compilation log: \n\n" << szInfoLog << std::endl;
		exit(EXIT_FAILURE);
	}

	hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* szFragment = fragmentShader.c_str();
	glShaderSource(hFragmentShader, 1, &szFragment, NULL);
	glCompileShader(hFragmentShader);

	//check for compilation errors
	glGetShaderiv(hFragmentShader, GL_COMPILE_STATUS, &compile);
	if(compile==GL_FALSE){
		std::cerr << "Fragment shader compilation failed\n";
		char szInfoLog[1024];
		glGetShaderInfoLog(hFragmentShader, 1024, NULL, szInfoLog);
		std::cerr << "Compilation log: \n\n" << szInfoLog << std::endl;
		exit(EXIT_FAILURE);
	}

	//create shader program and attach shaders
	hShaderProgram = glCreateProgram();

	glAttachShader(hShaderProgram, hVertexShader);
	glAttachShader(hShaderProgram, hFragmentShader);

	glLinkProgram(hShaderProgram);

	GLint linked;
	glGetProgramiv(hShaderProgram, GL_LINK_STATUS, &linked);
	if(!linked){
		std::cerr << "\nError linking shader.\n";
		char szInfoLog[1024];
		glGetProgramInfoLog(hShaderProgram, 1024, NULL, szInfoLog);
		std::cerr << "Compilation log: \n\n" << szInfoLog << std::endl;
		exit(EXIT_FAILURE);
	}
	glBindFragDataLocation(hShaderProgram, 0, "out_Color");
}

Shader::~Shader() {
	glDetachShader(hShaderProgram, hVertexShader);
	glDetachShader(hShaderProgram, hFragmentShader);
	glDeleteShader(hVertexShader);
	glDeleteShader(hFragmentShader);
	glDeleteProgram(hShaderProgram);
}

void Shader::use(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix) {
	glUseProgram(hShaderProgram);
	GLint modelViewMatrixLocation = glGetUniformLocation(hShaderProgram, "ModelViewMatrix");
	GLint projectionMatrixLocation = glGetUniformLocation(hShaderProgram, "ProjectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix.cArray); // Send our projection matrix to the shader
	glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, modelViewMatrix.cArray); // Send our modelview matrix to the shader
}

} /* namespace helsing */
