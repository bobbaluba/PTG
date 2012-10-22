#include "TextFile.h"

#include <fstream>
#include <sstream>
#include <iostream>

helsing::TextFile::TextFile(const std::string filename){
	std::ifstream t(filename.c_str());
	if(!t || !t.good()){
		std::cerr << "couldn't open file: " << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	std::stringstream buffer;
	buffer << t.rdbuf();
	data = buffer.str();
}

