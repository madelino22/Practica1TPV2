#pragma once


#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../ecs/Manager.h"


class Follow : public Component {
public:
	Follow():
		nave(nullptr),
		tr_(nullptr) {

		
	}
	Follow(Entity* nave_) :
		nave(nave_),
		tr_(nullptr) {
	}
	virtual ~Follow() {
	}



	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		//localiza mediante un handler la posición de l nave
		if(nave == nullptr) nave = entity_->getMngr()->getHandler<Jet>();

		auto& q = nave->getComponent<Transform>()->getPos();
		auto& p = tr_->getPos();
		auto& v = tr_->getVel();

		//como la velocidad inicial ya ha sido establecida al crear la entidad solo
		//hace falta rotar ese vector para que se aliniee con la nave
		v = v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f);
	}

private:
	Entity* nave;
	Transform* tr_;
};