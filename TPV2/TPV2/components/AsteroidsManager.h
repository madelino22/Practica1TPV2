#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "State.h"
#include "../ecs/Entity.h"

using Point2D = Vector2D;

class AsteroidsManager : public Component {
public:
    AsteroidsManager()
    {
    }
    virtual ~AsteroidsManager() {
    }



    void update() override {
       
    }




    void generaAsteroide() {
		Entity* asteroide = entity_->getMngr()->addEntity();

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
			asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroideOro"), 5, 6, 0, 0);
			asteroide->addComponent<Follow>();
			asteroide->addComponent<Generations>();

		}
		else {
			asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroide"), 5, 6, 0, 0);
			asteroide->addComponent<Generations>();
		}
		asteroide->addComponent<ShowAtOppositeSide>();

    }

private:

};