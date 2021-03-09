
#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class DisableOnExit : public Component {
public:
	DisableOnExit() :
		tr_(nullptr) {
	}
	virtual ~DisableOnExit() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto& pos = tr_->getPos();
		auto w = tr_->getW();
		auto h = tr_->getH();

		if (pos.getX() + w / 2 < 0 || pos.getX() + w / 2 > sdlutils().width() || pos.getY() + h / 2 < 0  || pos.getY() + h / 2 > sdlutils().height()) {
			entity_->setActive(false);
		}
	}

private:
	Transform* tr_;
};