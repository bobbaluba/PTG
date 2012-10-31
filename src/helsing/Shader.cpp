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

Shader::Shader(const std::string text) {
	hVertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* szVertex = text.c_str();
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
	}
}

Shader::~Shader() {
	// TODO Auto-generated destructor stub
}

} /* namespace helsing */
