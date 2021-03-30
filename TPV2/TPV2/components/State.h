#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"





class State : public Component {

public:
	enum States { NEWGAME, PAUSED, RUNNING, GAMEOVER, WON};

	State() {
		// Al empezar la partida el estado inicial es NEWGAME
		state = States::NEWGAME;

		//genera todos los mensjaes para cuando sean usados
		NEWGAMEText = &sdlutils().msgs().at("NEWGAME");
		PAUSEDText = &sdlutils().msgs().at("PAUSED");
		WINNERText = &sdlutils().msgs().at("WINNER");
		GAMEOVERText = &sdlutils().msgs().at("GAMEOVER");
		
		
	}
	virtual ~State() {
	}
	// Cambia el estado actual
	void changeState(States newState) {
		state = newState;
	}

	States getState() const { return state;}

		
	virtual void render() {
		//en función del estado se muestra un mensaje uotro por pantalla
		if (state == NEWGAME) {
			NEWGAMEText->render(200, 200);

		}
		else if (state == PAUSED) {
			PAUSEDText->render(200, 200);

		}
		else if (state == GAMEOVER) {
			GAMEOVERText->render(200, 200);

		}
		else if (state == WON) {
			WINNERText->render(200, 200);

		}

	}
	

private:
	States state;

	//los mensajes son texturas que usan el json y luego se pintan con render en la posición requerida
	Texture* NEWGAMEText;
	Texture* PAUSEDText;
	Texture* WINNERText;
	Texture* GAMEOVERText;
};