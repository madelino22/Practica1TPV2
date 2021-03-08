
#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class ShowAtOppositeSide : public Component {
public:
	ShowAtOppositeSide() :
		tr_(nullptr) {
	}
	virtual ~ShowAtOppositeSide() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto& pos = tr_->getPos();
		auto& vel = tr_->getVel();
		auto w = tr_->getW();
		auto h = tr_->getH();

		if (pos.getX() + w / 2 < 0) {
			pos.setX(sdlutils().width() - w/2);
		}
		else if (pos.getX() + w / 2 > sdlutils().width()) {
			pos.setX(-w / 2);
		}

		if (pos.getY() + h / 2 < 0) {
			pos.setY(sdlutils().height() - h/2);
		}
		else if (pos.getY()+h/2 > sdlutils().height()) {
			pos.setY(-h / 2);

		}

	}

private:
	Transform* tr_;
};