// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

#include "Transform.h"

class Image: public Component {
public:

	Image(Texture* tex) :
		tr_(nullptr), //
		tex_(tex), src_({0,0, tex_->width(), tex_->height()}) //

	{

	}



	Image(Texture *tex, SDL_Rect src) :
			tr_(nullptr), //
			tex_(tex), src_(src) //
			
	{

	}

	
	
	virtual ~Image() {
	}

	//Se necesita el transform para acceder a posición, ancho, alto y rotación del objeto que se va a dibujar
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH()); // Rectangulo destino donde se va a dibujar el objeto en pantalla
		tex_->render(src_, dest, tr_->getRot());
	}

private:
	Transform *tr_;
	Texture *tex_;
	SDL_Rect src_;
};

