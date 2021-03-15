#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"





class State : public Component {

public:
	enum States { NEWGAME, PAUSED, RUNNING, GAMEOVER };

	State() {
		state = NEWGAME;
	}
	virtual ~State() {
	}
	
	void changeState(States newState) {
		state = newState;
	}

	States getState() const { return state;}


	void update() override {
		if (state == NEWGAME) {

		}
		else if (state == PAUSED) {
			
		}
		else if (state = GAMEOVER) {

		}
	}

private:
	States state;
};