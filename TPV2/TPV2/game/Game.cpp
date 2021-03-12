// This file is part of the course TPV2@UCM - Samir Genaim


#include "Game.h"

#include "../components/Bounce.h"
#include "../components/KeyBoardCtrl.h"
#include "../components/Image.h"
#include "../components/Rectangle.h"
#include "../components/Transform.h"
#include "../components/Rotate.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Follow.h"
#include "../components/DisableOnExit.h"
#include "../components/Gun.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"


using Point2D = Vector2D;
//struct JET;

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}


void Game::generaAsteroide(Entity* jet) {
	auto* asteroide = mngr_->addEntity();

	int posIniR = sdlutils().rand().nextInt(0, 4);		

	Vector2D posIni;
	if (posIniR == 0) {
		posIni = Vector2D(0, sdlutils().rand().nextInt(0, sdlutils().height()));
	}
	else if (posIniR == 1) {
		posIni = Vector2D(sdlutils().width(), sdlutils().rand().nextInt(0, sdlutils().height()));
	}
	else if (posIniR == 2) {
		posIni = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), 0);
	}
	else {
		posIni = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().height());

	}


	//cálculo de velIni
	//point2d es un vector2d pero con el nombrecambiado para que sea más claro
	Point2D r = Point2D(sdlutils().rand().nextInt(0, 100), sdlutils().rand().nextInt(0, 100));
	//-50 para que quede centrado
	Point2D c = Point2D(sdlutils().width() / 2 - 50, sdlutils().height() / 2 - 50);

	c = c + r;

	Vector2D velIni = Vector2D((c - posIni).normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0)
	);




	asteroide->addComponent<Transform>(
		posIni,
		velIni, 25.0f, 25.0f, 0.0f);

	int gold = sdlutils().rand().nextInt(1, 10);
	if (gold >= 7) {
		asteroide->addComponent<Image>(&sdlutils().images().at("asteroideOro"), 5, 6, 0, 0);
		asteroide->addComponent<Follow>(jet);
	}
	else {
		asteroide->addComponent<Image>(&sdlutils().images().at("asteroide"), 5, 6, 0, 0);

	}
	asteroide->addComponent<ShowAtOppositeSide>();

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
	jet->addComponent<DeAcceleration>();
	jet->addComponent<ShowAtOppositeSide>();
	jet->addComponent<Gun>();

	//mngr_->setHandler<JET>(jet);

	//asteoride
	for (int x = 0; x < 10; x++) {
		generaAsteroide(jet);
	}
	

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

