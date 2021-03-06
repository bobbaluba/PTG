/**
 * @file Application.hpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <helsing/NonCopyable.hpp>

#include <helsing/Keyboard.hpp>

#include <string>

namespace helsing {

class Application: public NonCopyable{
public:
	class ApplicationSettings {
	public:
		explicit ApplicationSettings():
			width(800),
			height(600),
			depthBits(32),
			windowTitle("My Application"),
			fullscreen(false){
		}
		unsigned int width, height;
		unsigned int depthBits;
		std::string windowTitle;
		bool fullscreen;
	};
	Application(){}
	virtual ~Application();
	virtual void start() = 0;
	virtual void stop(){};
	virtual bool isRunning(){return false;};
	virtual bool isKeyDown(Keyboard::Key) = 0;
protected:
	virtual void onInit(){}
	virtual void onRender(){}
	virtual void onResize(unsigned int width, unsigned int height){}
	virtual void onClosed();
	virtual void onKeyPressed(Keyboard::Key key){if(key==Keyboard::ESCAPE)stop();}
	virtual void onMousePressed(bool left){}
};

} // namespace helsing
#endif // APPLICATION_HPP
