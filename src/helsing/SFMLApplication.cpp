/**
 * @file SFMLApplication.cpp
 * @date 21. nov. 2012
 * @author Johan Klokkhammer Helsing
 */
#include <helsing/SFMLApplication.hpp>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <cstdlib>
#include <cassert>
#include <iostream>

namespace {

helsing::Keyboard::Key toHelsingKey(sf::Keyboard::Key sfkey) {
	switch(sfkey){
	case sf::Keyboard::A:
		return helsing::Keyboard::A;
	case sf::Keyboard::B:
		return helsing::Keyboard::B;
	case sf::Keyboard::C:
		return helsing::Keyboard::C;
	case sf::Keyboard::D:
		return helsing::Keyboard::D;
	case sf::Keyboard::E:
		return helsing::Keyboard::E;
	case sf::Keyboard::F:
		return helsing::Keyboard::F;
	case sf::Keyboard::G:
		return helsing::Keyboard::G;
	case sf::Keyboard::H:
		return helsing::Keyboard::H;
	case sf::Keyboard::I:
		return helsing::Keyboard::I;
	case sf::Keyboard::J:
		return helsing::Keyboard::J;
	case sf::Keyboard::K:
		return helsing::Keyboard::K;
	case sf::Keyboard::L:
		return helsing::Keyboard::L;
	case sf::Keyboard::M:
		return helsing::Keyboard::M;
	case sf::Keyboard::N:
		return helsing::Keyboard::N;
	case sf::Keyboard::O:
		return helsing::Keyboard::O;
	case sf::Keyboard::P:
		return helsing::Keyboard::P;
	case sf::Keyboard::Q:
		return helsing::Keyboard::Q;
	case sf::Keyboard::R:
		return helsing::Keyboard::R;
	case sf::Keyboard::S:
		return helsing::Keyboard::S;
	case sf::Keyboard::T:
		return helsing::Keyboard::T;
	case sf::Keyboard::U:
		return helsing::Keyboard::U;
	case sf::Keyboard::V:
		return helsing::Keyboard::V;
	case sf::Keyboard::W:
		return helsing::Keyboard::W;
	case sf::Keyboard::X:
		return helsing::Keyboard::X;
	case sf::Keyboard::Y:
		return helsing::Keyboard::Y;
	case sf::Keyboard::Z:
		return helsing::Keyboard::Z;
	case sf::Keyboard::Num0:
		return helsing::Keyboard::NUMBER_0;
	case sf::Keyboard::Num1:
		return helsing::Keyboard::NUMBER_1;
	case sf::Keyboard::Num2:
		return helsing::Keyboard::NUMBER_2;
	case sf::Keyboard::Num3:
		return helsing::Keyboard::NUMBER_3;
	case sf::Keyboard::Num4:
		return helsing::Keyboard::NUMBER_4;
	case sf::Keyboard::Num5:
		return helsing::Keyboard::NUMBER_5;
	case sf::Keyboard::Num6:
		return helsing::Keyboard::NUMBER_6;
	case sf::Keyboard::Num7:
		return helsing::Keyboard::NUMBER_7;
	case sf::Keyboard::Num8:
		return helsing::Keyboard::NUMBER_8;
	case sf::Keyboard::Num9:
		return helsing::Keyboard::NUMBER_9;
	case sf::Keyboard::Escape:
		return helsing::Keyboard::ESCAPE;
	case sf::Keyboard::LControl:
		return helsing::Keyboard::LEFT_CONTROL;
	case sf::Keyboard::LShift:
		return helsing::Keyboard::LEFT_SHIFT;
	case sf::Keyboard::LAlt:
		return helsing::Keyboard::LEFT_ALT;
	case sf::Keyboard::LSystem:
		return helsing::Keyboard::LEFT_SUPER;
	case sf::Keyboard::RControl:
		return helsing::Keyboard::RIGHT_CONTROL;
	case sf::Keyboard::RShift:
		return helsing::Keyboard::RIGHT_SHIFT;
	case sf::Keyboard::RAlt:
		return helsing::Keyboard::RIGHT_ALT;
	case sf::Keyboard::RSystem:
		return helsing::Keyboard::RIGHT_SUPER;
	case sf::Keyboard::Menu:
		return helsing::Keyboard::MENU;
	case sf::Keyboard::LBracket:
		return helsing::Keyboard::LEFT_BRACKET;
	case sf::Keyboard::RBracket:
		return helsing::Keyboard::RIGHT_BRACKET;
	case sf::Keyboard::SemiColon:
		return helsing::Keyboard::SEMICOLON;
	case sf::Keyboard::Comma:
		return helsing::Keyboard::COMMA;
	case sf::Keyboard::Period:
		return helsing::Keyboard::PERIOD;
	case sf::Keyboard::Quote:
		return helsing::Keyboard::QUOTE;
	case sf::Keyboard::Slash:
		return helsing::Keyboard::SLASH;
	case sf::Keyboard::BackSlash:
		return helsing::Keyboard::BACKSLASH;
	case sf::Keyboard::Tilde:
		return helsing::Keyboard::TILDE;
	case sf::Keyboard::Equal:
		return helsing::Keyboard::EQUAL;
	case sf::Keyboard::Dash:
		return helsing::Keyboard::DASH;
	case sf::Keyboard::Space:
		return helsing::Keyboard::SPACE;
	case sf::Keyboard::Return:
		return helsing::Keyboard::RETURN;
	case sf::Keyboard::Up:
		return helsing::Keyboard::UP;
	case sf::Keyboard::Down:
		return helsing::Keyboard::DOWN;
	case sf::Keyboard::Left:
		return helsing::Keyboard::LEFT;
	case sf::Keyboard::Right:
		return helsing::Keyboard::RIGHT;
	case sf::Keyboard::F1:
		return helsing::Keyboard::F1;
	case sf::Keyboard::F2:
		return helsing::Keyboard::F2;
	case sf::Keyboard::F3:
		return helsing::Keyboard::F3;
	case sf::Keyboard::F4:
		return helsing::Keyboard::F4;
	case sf::Keyboard::F5:
		return helsing::Keyboard::F5;
	case sf::Keyboard::F6:
		return helsing::Keyboard::F6;
	case sf::Keyboard::F7:
		return helsing::Keyboard::F7;
	case sf::Keyboard::F8:
		return helsing::Keyboard::F8;
	case sf::Keyboard::F9:
		return helsing::Keyboard::F9;
	case sf::Keyboard::F10:
		return helsing::Keyboard::F10;
	case sf::Keyboard::F11:
		return helsing::Keyboard::F11;
	case sf::Keyboard::F12:
		return helsing::Keyboard::F12;
	default:
		std::cout << "Unknown key from sfml to helsing: " << sfkey << "\n";
		return helsing::Keyboard::UNKNOWN;
	}
}

sf::Keyboard::Key toSfKey(helsing::Keyboard::Key hkey){
	switch(hkey){
	case helsing::Keyboard::A:
		return sf::Keyboard::A;
	case helsing::Keyboard::B:
		return sf::Keyboard::B;
	case helsing::Keyboard::C:
		return sf::Keyboard::C;
	case helsing::Keyboard::D:
		return sf::Keyboard::D;
	case helsing::Keyboard::E:
		return sf::Keyboard::E;
	case helsing::Keyboard::F:
		return sf::Keyboard::F;
	case helsing::Keyboard::G:
		return sf::Keyboard::G;
	case helsing::Keyboard::H:
		return sf::Keyboard::H;
	case helsing::Keyboard::I:
		return sf::Keyboard::I;
	case helsing::Keyboard::J:
		return sf::Keyboard::J;
	case helsing::Keyboard::K:
		return sf::Keyboard::K;
	case helsing::Keyboard::L:
		return sf::Keyboard::L;
	case helsing::Keyboard::M:
		return sf::Keyboard::M;
	case helsing::Keyboard::N:
		return sf::Keyboard::N;
	case helsing::Keyboard::O:
		return sf::Keyboard::O;
	case helsing::Keyboard::P:
		return sf::Keyboard::P;
	case helsing::Keyboard::Q:
		return sf::Keyboard::Q;
	case helsing::Keyboard::R:
		return sf::Keyboard::R;
	case helsing::Keyboard::S:
		return sf::Keyboard::S;
	case helsing::Keyboard::T:
		return sf::Keyboard::T;
	case helsing::Keyboard::U:
		return sf::Keyboard::U;
	case helsing::Keyboard::V:
		return sf::Keyboard::V;
	case helsing::Keyboard::W:
		return sf::Keyboard::W;
	case helsing::Keyboard::X:
		return sf::Keyboard::X;
	case helsing::Keyboard::Y:
		return sf::Keyboard::Y;
	case helsing::Keyboard::Z:
		return sf::Keyboard::Z;
	case helsing::Keyboard::NUMBER_0:
		return sf::Keyboard::Num0;
	case helsing::Keyboard::NUMBER_1:
		return sf::Keyboard::Num1;
	case helsing::Keyboard::NUMBER_2:
		return sf::Keyboard::Num2;
	case helsing::Keyboard::NUMBER_3:
		return sf::Keyboard::Num3;
	case helsing::Keyboard::NUMBER_4:
		return sf::Keyboard::Num4;
	case helsing::Keyboard::NUMBER_5:
		return sf::Keyboard::Num5;
	case helsing::Keyboard::NUMBER_6:
		return sf::Keyboard::Num6;
	case helsing::Keyboard::NUMBER_7:
		return sf::Keyboard::Num7;
	case helsing::Keyboard::NUMBER_8:
		return sf::Keyboard::Num8;
	case helsing::Keyboard::NUMBER_9:
		return sf::Keyboard::Num9;
	case helsing::Keyboard::ESCAPE:
		return sf::Keyboard::Escape;
	case helsing::Keyboard::LEFT_CONTROL:
		return sf::Keyboard::LControl;
	case helsing::Keyboard::LEFT_SHIFT:
		return sf::Keyboard::LShift;
	case helsing::Keyboard::LEFT_ALT:
		return sf::Keyboard::LAlt;
	case helsing::Keyboard::LEFT_SUPER:
		return sf::Keyboard::LSystem;
	case helsing::Keyboard::RIGHT_CONTROL:
		return sf::Keyboard::RControl;
	case helsing::Keyboard::RIGHT_SHIFT:
		return sf::Keyboard::RShift;
	case helsing::Keyboard::RIGHT_ALT:
		return sf::Keyboard::RAlt;
	case helsing::Keyboard::RIGHT_SUPER:
		return sf::Keyboard::RSystem;
	case helsing::Keyboard::MENU:
		return sf::Keyboard::Menu;
	case helsing::Keyboard::LEFT_BRACKET:
		return sf::Keyboard::LBracket;
	case helsing::Keyboard::RIGHT_BRACKET:
		return sf::Keyboard::RBracket;
	case helsing::Keyboard::SEMICOLON:
		return sf::Keyboard::SemiColon;
	case helsing::Keyboard::COMMA:
		return sf::Keyboard::Comma;
	case helsing::Keyboard::PERIOD:
		return sf::Keyboard::Period;
	case helsing::Keyboard::QUOTE:
		return sf::Keyboard::Quote;
	case helsing::Keyboard::SLASH:
		return sf::Keyboard::Slash;
	case helsing::Keyboard::BACKSLASH:
		return sf::Keyboard::BackSlash;
	case helsing::Keyboard::TILDE:
		return sf::Keyboard::Tilde;
	case helsing::Keyboard::EQUAL:
		return sf::Keyboard::Equal;
	case helsing::Keyboard::DASH:
		return sf::Keyboard::Dash;
	case helsing::Keyboard::SPACE:
		return sf::Keyboard::Space;
	case helsing::Keyboard::RETURN:
		return sf::Keyboard::Return;
	case helsing::Keyboard::UP:
		return sf::Keyboard::Up;
	case helsing::Keyboard::DOWN:
		return sf::Keyboard::Down;
	case helsing::Keyboard::LEFT:
		return sf::Keyboard::Left;
	case helsing::Keyboard::RIGHT:
		return sf::Keyboard::Right;
	case helsing::Keyboard::F1:
		return sf::Keyboard::F1;
	case helsing::Keyboard::F2:
		return sf::Keyboard::F2;
	case helsing::Keyboard::F3:
		return sf::Keyboard::F3;
	case helsing::Keyboard::F4:
		return sf::Keyboard::F4;
	case helsing::Keyboard::F5:
		return sf::Keyboard::F5;
	case helsing::Keyboard::F6:
		return sf::Keyboard::F6;
	case helsing::Keyboard::F7:
		return sf::Keyboard::F7;
	case helsing::Keyboard::F8:
		return sf::Keyboard::F8;
	case helsing::Keyboard::F9:
		return sf::Keyboard::F9;
	case helsing::Keyboard::F10:
		return sf::Keyboard::F10;
	case helsing::Keyboard::F11:
		return sf::Keyboard::F11;
	case helsing::Keyboard::F12:
		return sf::Keyboard::F12;
	default:
		std::cout << "Unknown key from helsing to sfml\n";
		return sf::Keyboard::Unknown;
	}
}

} //anonymous namespace

namespace helsing {

SFMLApplication::SFMLApplication(const ApplicationSettings& settings):
		settings(settings),
		running(false),
		window(NULL){
}

void SFMLApplication::start(){
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
		std::cout << "Failed to initialize glew!\n";
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
			//default handling of events
			switch (event.type) {
			case sf::Event::Closed:
				onClosed();
				break;
			case sf::Event::KeyPressed:
				{
					sf::Keyboard::Key sfkey = event.key.code;
					helsing::Keyboard::Key hkey = toHelsingKey(sfkey);
					onKeyPressed(hkey);
				}
				break;
			case sf::Event::Resized:
				onResize(event.size.width, event.size.height);
				break;
			default:
				break;
			}
		}
		if(running){
			window->setActive();
			onRender();
			window->display();
		}
	}
}

void SFMLApplication::stop(){
	window->close();
	delete window;
	running = false;
}

bool SFMLApplication::isKeyDown(Keyboard::Key key) {
	return sf::Keyboard::isKeyPressed(toSfKey(key));
}

} /* namespace helsing */
