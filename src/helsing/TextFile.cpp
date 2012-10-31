/**
 * @file TextFile.cpp
 * @date 2012
 * @author Johan Klokkhammer Helsing
 */
#include <helsing/TextFile.hpp>

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

