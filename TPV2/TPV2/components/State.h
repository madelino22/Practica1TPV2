#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"





class State : public Component {

public:
	enum States { NEWGAME, PAUSED, RUNNING, GAMEOVER};

	State() {
		state = States::NEWGAME;
		NEWGAMEText = &sdlutils().msgs().at("NEWGAME");
		PAUSEDText = &sdlutils().msgs().at("PAUSED");
		WINNERText = &sdlutils().msgs().at("WINNER");
		GAMEOVERText = &sdlutils().msgs().at("GAMEOVER");
		
		
	}
	virtual ~State() {
	}
	
	void changeState(States newState) {
		state = newState;
	}

	States getState() const { return state;}

		
	virtual void render() {
		if (state == NEWGAME) {
			NEWGAMEText->render(200, 200);

		}
		else if (state == PAUSED) {
			PAUSEDText->render(200, 200);

		}
		else if (state == GAMEOVER) {
			GAMEOVERText->render(200, 200);

		}

	}
	void update() override {
		
		
	}

private:
	States state;

	Texture* NEWGAMEText;
	Texture* PAUSEDText;
	Texture* WINNERText;
	Texture* GAMEOVERText;
};