/**
 * @file Application.cpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */
#include <helsing/Application.hpp>

#include <GL/glew.h>

#include <cstdlib>
#include <cassert>
#include <iostream>

namespace helsing {

Application::Application(const ApplicationSettings& settings):
		window(NULL),
		settings(settings),
		running(false) {
}

Application::~Application() {
	if(running)stop();
}

void Application::start(){
	sf::ContextSettings contextSettings;
	contextSettings.majorVersion = 2;
	contextSettings.minorVersion = 1;

	if(settings.fullscreen){
		auto videoMode = sf::VideoMode::getDesktopMode();
		window = new sf::RenderWindow(videoMode, settings.windowTitle, sf::Style::Fullscreen, contextSettings);
	} else {
		auto videoMode = sf::VideoMode(settings.width, settings.height);
		window = new sf::RenderWindow(videoMode, settings.windowTitle, sf::Style::Default, contextSettings);
	}
	if (GLEW_OK != glewInit())
	{
	    // GLEW failed!
	    exit(1);
	}
	if (!GLEW_VERSION_2_1){  // check that the machine supports the 2.1 API.
		std::cerr << "OpenGL 2.1 API not supported!\n";
		exit(1); // or handle the error in a nicer way
	}
	onInit();
	running = true;
	while(running){
		sf::Event event;
		while (window->pollEvent(event) && running) {
			if(handleEvent(event)){
				//subclass handled event, skip to next event
				continue;
			}
			//default handling of events
			switch (event.type) {
			case sf::Event::Closed:
				stop();
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape){
					stop();
				}
				break;
			case sf::Event::Resized:
				onResize(event.size.width, event.size.height);
				break;
			default:
				break;
			}
		}
		if(running)onRender();
	}
}

void Application::stop(){
	window->close();
	delete window;
	running = false;
}

void Application::onRender(){
	window->setActive();
	window->display();
}

} /* namespace helsing */
