/*
 * SceneApplication.h
 *
 *  Created on: 25. sep. 2012
 *      Author: johan
 */

#ifndef SCENEAPPLICATION_H_
#define SCENEAPPLICATION_H_

#include "helsing/Application.h"
#include "Scene.h"

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

#endif /* SCENEAPPLICATION_H_ */