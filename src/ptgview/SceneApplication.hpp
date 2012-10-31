/**
 * @file SceneApplication.hpp
 * @date 25. sep. 2012
 * @author Johan Klokkhammer Helsing
 */

#ifndef SCENEAPPLICATION_HPP
#define SCENEAPPLICATION_HPP

#include "Scene.hpp"

#include <helsing/Application.hpp>

class LayoutApplication: public helsing::Application {
public:
	LayoutApplication(const ApplicationSettings& = ApplicationSettings());
	virtual ~LayoutApplication();

	virtual void setScene(Scene* scene);
	virtual Scene* getScene() const {return scene;}

	virtual void onRender(){scene->render();}
	virtual bool handleInput(const sf::Event& event){return scene->handleEvent(event);}
private:
	Scene* scene;
};

#endif /* SCENEAPPLICATION_HPP */
