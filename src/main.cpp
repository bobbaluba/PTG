#include "config.h"

#include "LandscapeApplication.h"

#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>


using namespace helsing;
using namespace ptg;

using namespace std;

int main(int argc, char* argv[] ){
	cout << "PTG Version " << VERSION_MAJOR << "." << VERSION_MINOR << "\n\n";

	unsigned int heightMapSize=65;
	for(int i=1; i<argc; ++i){
		string argument(argv[i]);
		if(argument=="-h" || argument=="--help"){
			cout << "Command line Arguments:\n";
			cout << "\t-d <number>, --dimensions <number>:\tSet the width of the HeightMap\n";
			cout << "\t-h, --help\t\t\t\tDisplay this help screen\n";
			cout << endl;
			return EXIT_SUCCESS;
		} else if (argument=="-d" || argument=="--dimensions"){
			if(++i<argc){
				string value(argv[i]);
				istringstream ss( value );
				ss >> heightMapSize;
				if(heightMapSize==0) {
					cerr << "Error parsing dimensions, must be a positive integer\n";
					return EXIT_FAILURE;
				}
				cout << "Setting heightmap dimensions to: " << heightMapSize << endl;
			}
		}
	}

	LandscapeApplication app;
	app.setHeightMapSize(heightMapSize);
	app.start();
	cout << "\nClosing...\n\n";

	return 0;
}
