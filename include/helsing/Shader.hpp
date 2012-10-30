/*
 * Shader.hpp
 *
 *  Created on: 12. sep. 2012
 *      Author: Johan Klokkhammer Helsing
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <string>

namespace helsing {

class Shader {
public:
	Shader(const std::string text);
	virtual ~Shader();
private:
	unsigned int hVertexShader;
};

} /* namespace helsing */
#endif /* SHADER_H_ */
