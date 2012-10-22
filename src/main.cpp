#include "config.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "LandscapeApplication.h"

using namespace helsing;
using namespace landscape;

int main(int, char*[]){
	std::cout << "Version " << VERSION_MAJOR << "." << VERSION_MINOR << "\n";
	LandscapeApplication app;
	app.start();
	std::cout << "\nClosing...\n\n";

	return 0;
}
