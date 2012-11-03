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
		std::cerr << "Shader compilation failed\n";
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
		std::cerr << "Shader compilation failed\n";
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
}

Shader::~Shader() {
	glDetachShader(hShaderProgram, hVertexShader);
	glDetachShader(hShaderProgram, hFragmentShader);
	glDeleteShader(hVertexShader);
	glDeleteShader(hFragmentShader);
	glDeleteProgram(hShaderProgram);
}

} /* namespace helsing */
