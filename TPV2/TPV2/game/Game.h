// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <memory>



// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;
class Entity;
class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:

	//este m�todo hay que quitarle
	std::unique_ptr<Manager> mngr_;
};

