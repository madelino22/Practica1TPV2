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
		//Se obtiene l alista de entidades
		auto& ents = entity_->getMngr()->getEnteties();
		int n = ents.size();
		//Se recorre la lista de entidades
		for (int i = 0; i < n; ++i)
			//para cada entidad del grupoi asteroides
			if (ents[i]->hasGroup<Asteroids>())
			{
				auto aTR = ents[i]->getComponent<Transform>();
				for (int j = 0; j < n; ++j)
					//se recorre otra vez la lista preguntando a las entidades del grupo balas o a la nave
					if (ents[j]->hasGroup<Bullets>()) // Choque con las balas
					{
						auto bTR = ents[j]->getComponent<Transform>();
						//si han chocado
						if (Collisions::collidesWithRotation(aTR->getPos(), aTR->getW(), aTR->getH(), aTR->getRot(),
							bTR->getPos(), bTR->getW(), bTR->getH(), bTR->getRot()))
						{

							entity_->getComponent<AsteroidsManager>()->onCollision(ents[i]);
							ents[j]->setActive(false);
							if (entity_->getComponent<AsteroidsManager>()->getNumAsteroides() == 0)
							{
								//si ya no quedan astaroides se gana la partida y se restablecen todas las variables
								entity_->getComponent<State>()->changeState(State::WON);
								auto tr_ = jet->getComponent<Transform>();
								tr_->setRot(0.0f);
								tr_->setVel(Vector2D(0, 0));
								tr_->setPos(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f));

								//Además se quitan las componenten que hacen que se mueva en el menu para que no se mueva,
								//luego, al cargar otra vez partida, se le vuelven a añadir
								jet->removeComponent<FighterCtrl>();
								jet->removeComponent<Gun>();
							}
						}
					}
					else if (ents[j]->hasComponent<FighterCtrl>()) // Choque con la nave
					{
						auto jTR = ents[j]->getComponent<Transform>();
						if (Collisions::collidesWithRotation(aTR->getPos(), aTR->getW(), aTR->getH(), aTR->getRot(),
							jTR->getPos(), jTR->getW(), jTR->getH(), jTR->getRot()))
						{
							desactivaEntidades();
							auto jetHealth = jet->getComponent<Health>();
							// El jugador pierde una vida
							jetHealth->loseLife();
							auto tr_ = jet->getComponent<Transform>();
							// El caza vuelve al centro de la pantalla con velocidad nula y orientado hacia arriba
							tr_->setRot(0.0f);
							tr_->setVel(Vector2D(0, 0));
							tr_->setPos(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f));
							// Se eliminan los componentes de accion del caza para que no se pueda mover ni disparar hasta que comience la partida
							jet->removeComponent<FighterCtrl>();
							jet->removeComponent<Gun>();
							// Se reproduce un sonido
							sdlutils().soundEffects().at("bangSmall").play();
							// Si quedan vidas cambiamos al estado de pausa
							if (jetHealth->getLives() > 0)
								entity_->getComponent<State>()->changeState(State::PAUSED);
							// Si no, acaba la partida
							else entity_->getComponent<State>()->changeState(State::GAMEOVER);
						}
					}

			}
	}
	// Desactiva todas las balas y los asteroides
	void desactivaEntidades()
	{
		auto& ents = entity_->getMngr()->getEnteties();
		int n = ents.size();
		// Recorremos todas las entidades
		for (int i = 0; i < n; ++i)
		{
			// Desactivamos aquellas que sean asteroides o balas
			if (ents[i]->hasGroup<Asteroids>() || ents[i]->hasGroup<Bullets>())
			{
				ents[i]->setActive(false);
			}
		}

	}
private:
	Entity* jet;
};