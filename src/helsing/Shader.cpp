/**
 * @file Shader.cpp
 * @date 12. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#include <helsing/Shader.hpp>

#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>

namespace {

void handleCompilationLog(GLuint hShader, GLuint type){
	std::string shaderType = "Unknown";
	if(type == GL_VERTEX_SHADER){
		shaderType = "Vertex";
	} else if (type == GL_FRAGMENT_SHADER){
		shaderType = "Fragment";
	}

	GLint bufflen = 0;
	glGetShaderiv(hShader, GL_INFO_LOG_LENGTH, &bufflen);
	if(bufflen>1){
		GLchar* szInfoLog = new GLchar[bufflen+1];
		glGetShaderInfoLog(hShader, 1024, NULL, szInfoLog);
		std::cerr << "\n" << shaderType << "Vertex Shader Compilation log: \n\n" << szInfoLog << std::endl;
		delete szInfoLog;

		//check if it actually failed
		GLint compile;
		glGetShaderiv(hShader, GL_COMPILE_STATUS, &compile);
		if(compile==GL_FALSE){
			std::cerr << "\nError: " << shaderType << "shader compilation failed\n";
			exit(EXIT_FAILURE);
		}
	}
}

} // anonymous namespace

namespace helsing {

Shader::Shader(const std::string vertexShader, const std::string fragmentShader) {
	hVertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* szVertex = vertexShader.c_str();
	glShaderSource(hVertexShader, 1, &szVertex, NULL);
	glCompileShader(hVertexShader);

	//check for compilation errors
	handleCompilationLog(hVertexShader, GL_VERTEX_SHADER);

	hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* szFragment = fragmentShader.c_str();
	glShaderSource(hFragmentShader, 1, &szFragment, NULL);
	glCompileShader(hFragmentShader);

	//check for compilation errors
	handleCompilationLog(hFragmentShader, GL_FRAGMENT_SHADER);

	//create shader program and attach shaders
	hShaderProgram = glCreateProgram();

	glAttachShader(hShaderProgram, hVertexShader);
	glAttachShader(hShaderProgram, hFragmentShader);

	glLinkProgram(hShaderProgram);

	GLint linked;
	glGetProgramiv(hShaderProgram, GL_LINK_STATUS, &linked);
	if(!linked){
		//TODO are linker warnings possible? will i detect them?
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

void Shader::setUniform(const std::string uniform, float value) {
	GLuint hUniform = glGetUniformLocation(hShaderProgram, uniform.c_str());
	if(hUniform>=0){
		glUniform1f(hUniform, value);
	} else {
		std::cerr << "Cannot set uniform: Uniform not active\n";
		exit(EXIT_FAILURE);
	}
}

} /* namespace helsing */
