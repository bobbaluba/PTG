/**
 * @file Shader.hpp
 * @date 12. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <helsing/math/Mat4.hpp>

#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

namespace helsing {

class Shader {
public:
	Shader(const std::string vertexShader, const std::string fragmenShader);
	virtual ~Shader();
	virtual unsigned int getProgramHandle(){return hShaderProgram;}
	virtual GLint getPositionAttributeIndex(){return glGetAttribLocation(hShaderProgram,"in_Position");}
	virtual GLint getColorAttributeIndex(){return glGetAttribLocation(hShaderProgram,"in_Color");}
	virtual GLint getNormalAttributeIndex(){return glGetAttribLocation(hShaderProgram,"in_Normal");}
	virtual void use(const helsing::Mat4& modelViewMatrix, const helsing::Mat4& projectionMatrix);
private:
	GLuint hVertexShader;
	GLuint hFragmentShader;
	GLuint hShaderProgram;
};

} // namespace helsing
#endif // SHADER_HPP
