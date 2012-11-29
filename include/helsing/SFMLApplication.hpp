/**
 * @file SFMLApplication.hpp
 * @date 21. nov. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef SFMLAPPLICATION_HPP
#define SFMLAPPLICATION_HPP

#include <helsing/Application.hpp>

#include <helsing/Keyboard.hpp>

#include <SFML/Graphics.hpp>

#include <string>

namespace helsing {

class SFMLApplication: public Application{
public:
	explicit SFMLApplication(const ApplicationSettings& = ApplicationSettings());
	virtual void start();
	virtual void stop();
	virtual bool isRunning(){return running;}
	virtual bool isKeyDown(Keyboard::Key);
protected:
	const ApplicationSettings settings;
	bool running;
	sf::RenderWindow * window;
};

} // namespace helsing
#endif // SFMLAPPLICATION_HPP
