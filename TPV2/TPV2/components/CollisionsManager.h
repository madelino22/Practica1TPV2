#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "State.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"
#include "../utils/Collisions.h"
#include "../ecs/Manager.h"
#include "../components/AsteroidsManager.h"
using Point2D = Vector2D;

class CollisionsManager : public Component {
public:
	CollisionsManager()
	{
		jet = nullptr;
		
	}
	virtual ~CollisionsManager() {
	}


	void refreshJet()
	{
		jet = entity_->getMngr()->getHandler<Jet>();
	}
	void update() override {
		auto& ents = entity_->getMngr()->getEnteties();
		int n = ents.size();
		for (int i = 0; i < n; ++i)
			if (ents[i]->hasGroup<Asteroids>())
			{
				auto aTR = ents[i]->getComponent<Transform>();
				for (int j = 0; j < n; ++j)
					if (ents[j]->hasGroup<Bullets>())
					{
						auto bTR = ents[j]->getComponent<Transform>();
						if (Collisions::collidesWithRotation(aTR->getPos(), aTR->getW(), aTR->getH(), aTR->getRot(),
							bTR->getPos(), bTR->getW(), bTR->getH(), bTR->getRot()))
						{
							entity_->getComponent<AsteroidsManager>()->onCollision(ents[i]);
							ents[j]->setActive(false);
						}
					}
					else if (ents[j]->hasComponent<FighterCtrl>())
					{
						auto jTR = ents[j]->getComponent<Transform>();
						if (Collisions::collidesWithRotation(aTR->getPos(), aTR->getW(), aTR->getH(), aTR->getRot(),
							jTR->getPos(), jTR->getW(), jTR->getH(), jTR->getRot()))
						{
							Catapum();
							auto jetHealth = jet->getComponent<Health>();
							jetHealth->loseLife();
							
							if (jetHealth->getLives() > 0)
								entity_->getComponent<State>()->changeState(State::PAUSED);
							else entity_->getComponent<State>()->changeState(State::GAMEOVER);
						}
					}

			}
	}
	// Desactiva todas las balas y los asteroides
	void Catapum()
	{
		auto& ents = entity_->getMngr()->getEnteties();
		int n = ents.size();
		for (int i = 0; i < n; ++i)
		{
			if (ents[i]->hasGroup<Asteroids>() || ents[i]->hasGroup<Bullets>())
			{
				ents[i]->setActive(false);
			}
		}

	}
private:
	Entity* jet;
};