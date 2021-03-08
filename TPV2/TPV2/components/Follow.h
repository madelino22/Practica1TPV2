#pragma once


#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class Follow : public Component {
public:
	Follow():
		tr_(nullptr) {
		jet = entity_->getMngr()->getHandler<JET>();
	}
	virtual ~Follow() {
	}



	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {

		auto& q = jet->addComponent<Transform>()->getPos();
		auto& p = tr_->getPos();
		auto& v = tr_->getVel();
		v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f);
	}

private:
	Entity* jet;
	Transform* tr_;
};