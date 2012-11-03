/**
 * @file Shader.hpp
 * @date 12. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

namespace helsing {

class Shader {
public:
	Shader(const std::string vertexShader, const std::string fragmenShader);
	virtual ~Shader();
private:
	unsigned int hVertexShader;
	unsigned int hFragmentShader;
	unsigned int hShaderProgram;
};

} // namespace helsing
#endif // SHADER_HPP
