/**
 * @file TextFile.hpp
 * @date 12. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef TEXTFILE_HPP
#define TEXTFILE_HPP

#include <string>

namespace helsing {

/** @brief Represents an plain text file
 *
 * Used to abstract away the horrible details of converting a text file to a string
 */
class TextFile {
public:
	/// @brief Initialise a text file
	/// @param filename Full or relative path to the file
	explicit TextFile(const std::string filename);
	std::string str() const {return data;}
private:
	std::string data;
};


} // namespace helsing
#endif // TEXTFILE_HPP
