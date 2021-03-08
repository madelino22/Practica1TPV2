#pragma once


#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class FighterCtrl : public Component {
public:
	FighterCtrl() :
		tr_(nullptr){
		
	}
	virtual ~FighterCtrl() {
	}



	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {


			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				Vector2D newVel;
				r = tr_->getRot();
				auto& vel = tr_->getVel();
				newVel = vel + Vector2D(0, -1).rotate(r) * thrust;
				if (newVel.magnitude() > speedLimit)
					newVel = newVel.normalize()*speedLimit;
				(vel).setX(newVel.getX());
				(vel).setY(newVel.getY());

			}
			

			if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				tr_->setRot(tr_->getRot() - 5.0f);
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				tr_->setRot(tr_->getRot() + 5.0f);
			}

		}
	}

private:
	float thrust = 0.2;
	float speedLimit = 3;
	float r;
	Transform* tr_;
};