/*
 * TextFile.hpp
 *
 *  Created on: 12. sep. 2012
 *      Author: Johan Klokkhammer Helsing
 */

#ifndef HFILE_H_
#define HFILE_H_

#include <string>

namespace helsing {

class TextFile {
public:
	TextFile(const std::string filename);
	std::string str() const {return data;}
private:
	std::string data;
};


}
#endif /* HFILE_H_ */
