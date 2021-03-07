// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Bounce.h"
#include "../components/KeyBoardCtrl.h"
#include "../components/Image.h"
#include "../components/Rectangle.h"
#include "../components/Transform.h"
#include "../components/Rotate.h"
#include "../components/FighterCtrl.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/resources.json");

	auto *jet = mngr_->addEntity();
	jet->addComponent<Transform>(
			Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
			Vector2D(), 50.0f, 50.0f, 0.0f);
	jet->addComponent<Image>(&sdlutils().images().at("nave"));
	jet->addComponent<FighterCtrl>();
	jet->addComponent<Bounce>();


}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

