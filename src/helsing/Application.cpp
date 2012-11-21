/**
 * @file Application.cpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */
#include <helsing/Application.hpp>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include <cstdlib>
#include <cassert>
#include <iostream>

namespace helsing {

} // namespace helsing

helsing::Application::~Application() {
	 if(isRunning())stop();
}

void helsing::Application::onClosed() {
	stop();
}
