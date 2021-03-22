#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "State.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"
using Point2D = Vector2D;

class AsteroidsManager : public Component {
public:
    AsteroidsManager()
    {
    }
    virtual ~AsteroidsManager() {
    }



    void update() override {
		if (entity_->getComponent<State>()->getState() == State::RUNNING)
		{
			if (sdlutils().currRealTime() >= timer + 5000)
			{
				timer = sdlutils().currRealTime();
				generaAsteroide();
			}
		}
    }
	void onCollision(Entity* as)
	{
		sdlutils().soundEffects().at("bangSmall").play();
		auto gen = (*as).getComponent<Generations>()->getGenerations();
		if (gen > 0)
		{
			divideAsteroide(as, gen);
			divideAsteroide(as, gen);
		}
		as->setGroup<Asteroids>(false);
		(*as).setActive(false);
		numAsteroides--;
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
		asteroide->addComponent<Generations>();
		int gen = asteroide->getComponent<Generations>()->getGenerations();
		asteroide->addComponent<Transform>(
			posIni,
			velIni, 10.0f + 5.0f * gen, 10.0f + 5.0f * gen, 0.0f);

		int gold = sdlutils().rand().nextInt(1, 10);
		if (gold >= 7) {
			asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroideOro"), 5, 6, 0, 0);
			asteroide->addComponent<Follow>();
		}
		else {
			asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroide"), 5, 6, 0, 0);			
		}
		asteroide->addComponent<ShowAtOppositeSide>();
		asteroide->setGroup<Asteroids>(true);
		numAsteroides++;
    }
	void divideAsteroide(Entity* as, int gen)
	{
		Entity* asteroide = entity_->getMngr()->addEntity();
		auto as_tr = as->getComponent<Transform>();
		Vector2D p = as_tr->getPos();
		Vector2D v = as_tr->getVel();
		int w= as_tr->getW();
		auto size = 10.0f + 5.0f * gen;
		int r = sdlutils().rand().nextInt(0, 360);
		asteroide->addComponent<Transform>(p + v.rotate(r) * 2 * w, v.rotate(r) * 1.1f, size, size, 0.0f);
		asteroide->addComponent<Generations>(gen-1);
		asteroide->addComponent<ShowAtOppositeSide>();
		if (as->hasComponent<Follow>())
		{
			asteroide->addComponent<Follow>();
			asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroideOro"), 5, 6, 0, 0);
		}
		else asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroide"), 5, 6, 0, 0);
		asteroide->setGroup<Asteroids>(true);
		numAsteroides++;
	}
	int getNumAsteroides()
	{
		return numAsteroides;
	}
private:
	int numAsteroides = 0;
	float timer;
};



