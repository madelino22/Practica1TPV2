// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class DeAcceleration : public Component {
public:
	DeAcceleration() :
		tr_(nullptr) {
	}
	virtual ~DeAcceleration() {
	}

	//Al iniciar guarda el componente transform ya que lo necesita para desacelerar
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	//en cada iteración del bicle de juego disminuye la velocidad poco a poco, cambiando la velocidad del componente transform
	void update() override {
		auto& vel = tr_->getVel();
		vel = vel * 0.995f;
	}

private:
	Transform* tr_;
};

