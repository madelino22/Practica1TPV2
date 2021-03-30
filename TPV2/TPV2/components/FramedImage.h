// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class FramedImage : public Component {
public:

	FramedImage(Texture* tex) :
		tr_(nullptr), //
		tex_(tex), src_({ 0,0, tex_->width(), tex_->height() }) //

	{

	}



	FramedImage(Texture* tex, SDL_Rect src) :
		tr_(nullptr), //
		tex_(tex), src_(src) //

	{

	}

	FramedImage(Texture* tex, int rows, int cols, int r, int c) :
		tr_(nullptr), //
		tex_(tex) //
	{	
		
		auto w = tex_->width() / cols; // Ancho de la imagen
		auto h = tex_->height() / rows; // Alto de la imagen
		src_ = { w * c, h * r, w, h };
	}
	virtual ~FramedImage() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}
	void update()
	{
		if (sdlutils().currRealTime() >= timer + 50) // Cada 50 ms debe cambiar el fragmento que cogemos de la textura
		{
			
			src_.x = src_.x + src_.w; // A la posición horizontal en la que estamos de la textura le sumamos el ancho de la imagen para que pasemos a la siguiente imagen del spritesheet
			if (src_.x >= tex_->width()) // Si al hacerlo superamos el ancho del spritesheet, pasamos a la siguiente fila empezando por la izquierda
			{
				src_.x = 0;
				src_.y = src_.y + src_.h;
			}
			if (src_.y >= tex_->height()) // Si superamos el alto del spritesheet, volvemos a empezar desde el principio
			{
				src_.y = 0;
			}
			timer = sdlutils().currRealTime(); // Actualizamos el contador
		}
	}
	void render() override {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH()); // Rectángulo de destino donde se debe dibujar la imagen
		tex_->render(src_, dest, tr_->getRot());
	}

private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_; // Rectángulo cuyas dimensiones equivalen a la parte que queremos de la imagen
	float timer; // Temporizador
};

