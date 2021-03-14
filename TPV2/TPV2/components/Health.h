// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class Health : public Component {
public:

	Health() :
		tr_(nullptr), tex_(&sdlutils().images().at("star")), //
		lives(3),src_({ 0,0, tex_->width(), tex_->height() }) //
	{}

	virtual ~Health() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}
	void loseLife()
	{
		lives = --lives;
	}
	void resetLives()
	{
		lives = 3;
	}
	int getLives()
	{
		return lives;
	}
	void render() override {
		Vector2D pos(tr_->getW(), tr_->getH());
		SDL_Rect dest = build_sdlrect(pos, tr_->getW(), tr_->getH());
		for (int i = 0; i < lives; ++i)
		{
			tex_->render(src_, dest, 0);
			dest.x = dest.x + tr_->getW() + 10;
		}
	}

private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_;
	int lives;
};

