// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class Generations : public Component {
public:

	Generations() :
		generations(sdlutils().rand().nextInt(1, 3))
	{}
	Generations(int g) :
		generations(g)
	{}

	virtual ~Generations() {
	}
	
	int getGenerations()
	{
		return generations;
	}

private:
	int generations;
};

