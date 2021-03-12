#pragma once


#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
class Gun : public Component {
public:
	Gun() :
		tr_(nullptr){	
	}
	
	virtual ~Gun() {
	}



	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDLK_s) && sdlutils().currRealTime() >= timer+250) {
				timer = sdlutils().currRealTime();
				Manager* mng = entity_->getMngr();
				Entity* balaTest = mng->addEntity();
				Vector2D p = tr_->getPos();
				Vector2D vel = tr_->getVel();
				float w = tr_->getW();
				float h = tr_->getH();
				float r = tr_->getRot();
				Vector2D bPos = p + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r) - Vector2D(2.0f, 10.0f);
				Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(r) * (vel.magnitude() + 5.0f);
				balaTest->addComponent<Transform>(
					bPos,
					bVel, 5.0f, 20.0f, r);
				balaTest->addComponent<Image>(&sdlutils().images().at("asteroide"));
				balaTest->addComponent<DisableOnExit>();

				balaTest->setGroup<Bullets>(true);
				sdlutils().soundEffects().at("fire").play();

			}
		}
	}

private:
	Transform* tr_;
	float timer;
};