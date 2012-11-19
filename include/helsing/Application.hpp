/**
 * @file Application.hpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

namespace helsing {

class Application {
public:
	class ApplicationSettings {
	public:
		ApplicationSettings():width(800),height(600), windowTitle("My Application"), fullscreen(false){}
		uint32_t width, height;
		std::string windowTitle;
		bool fullscreen;
	};
	Application(const ApplicationSettings& = ApplicationSettings());
	virtual ~Application();

	virtual void start();
	virtual void stop();

	virtual bool isRunning() const {return running;}
protected:
	virtual void onInit(){}
	virtual void onRender();
	virtual void onResize(uint32_t width, uint32_t height){}
	virtual bool handleEvent(const sf::Event& event){return false;}

//member data
protected:
	sf::RenderWindow * window;
private:
	const ApplicationSettings settings;
	bool running;
};

} /* namespace helsing */
#endif /* APPLICATION_HPP */
