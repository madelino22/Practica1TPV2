#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "State.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"
using Point2D = Vector2D;

class AsteroidsManager : public Component {
public:
    AsteroidsManager()
    {
    }
    virtual ~AsteroidsManager() {
    }



    void update() override {
		if (entity_->getComponent<State>()->getState() == State::RUNNING)
		{
			//timer + 5000 es la cadencia con la que se genera un asteroide (5 segundos)
			if (sdlutils().currRealTime() >= timer + 5000)
			{
				timer = sdlutils().currRealTime(); // Se actualiza el temporizador
				generaAsteroide();//metodo para generar un asteroide
			}
		}
    }
	// Cuando un asteroide impacta con una bala
	void onCollision(Entity* as)
	{
		// Se produce un sonido
		sdlutils().soundEffects().at("bangSmall").play();
		auto gen = (*as).getComponent<Generations>()->getGenerations();
		// Si al asteroide todavía le quedaban divisiones, se divide en dos asteroides con una generación menos
		if (gen > 0) 
		{
			divideAsteroide(as, gen);
			divideAsteroide(as, gen);
		}
		// Se desactiva el asteroide y se actualiza el numero total de los mismos
		as->setGroup<Asteroids>(false);
		(*as).setActive(false);
		numAsteroides--;
	}



    void generaAsteroide() {
		//Se añade la entidad
		Entity* asteroide = entity_->getMngr()->addEntity();

		//con este random se elige el margen en el que aparecerá el asateoride
		int posIniR = sdlutils().rand().nextInt(0, 4);

		Vector2D posIni;
		if (posIniR == 0) {
			posIni = Vector2D(0, sdlutils().rand().nextInt(0, sdlutils().height()));
		}
		else if (posIniR == 1) {
			posIni = Vector2D(sdlutils().width(), sdlutils().rand().nextInt(0, sdlutils().height()));
		}
		else if (posIniR == 2) {
			posIni = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), 0);
		}
		else {
			posIni = Vector2D(sdlutils().rand().nextInt(0, sdlutils().width()), sdlutils().height());

		}


		//cálculo de velIni
		//point2d es un vector2d pero con el nombrecambiado para que sea más claro
		Point2D r = Point2D(sdlutils().rand().nextInt(0, 100), sdlutils().rand().nextInt(0, 100));
		//-50 para que quede centrado
		Point2D c = Point2D(sdlutils().width() / 2 - 50, sdlutils().height() / 2 - 50);

		c = c + r;

		//velocidad inicial con factor aleatorio
		Vector2D velIni = Vector2D((c - posIni).normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0)
		);


		asteroide->addComponent<Generations>();
		//se guarda gen para ponerle el tamaño inicial al asteroide
		int gen = asteroide->getComponent<Generations>()->getGenerations();
		asteroide->addComponent<Transform>(
			posIni,
			velIni, 10.0f + 5.0f * gen, 10.0f + 5.0f * gen, 0.0f);

		//nuemro al azar que determina si es un asteroide de oro o no
		int gold = sdlutils().rand().nextInt(1, 10);
		if (gold >= 7) {
			asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroideOro"), 5, 6, 0, 0);
			asteroide->addComponent<Follow>();
		}
		else {
			asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroide"), 5, 6, 0, 0);			
		}
		asteroide->addComponent<ShowAtOppositeSide>();
		asteroide->setGroup<Asteroids>(true);
		//se actualiza el contador de asteroides
		numAsteroides++;
    }
	void divideAsteroide(Entity* as, int gen)
	{
		Entity* asteroide = entity_->getMngr()->addEntity();
		// Se coge el transform del asteroide del que proviene el nuevo
		auto as_tr = as->getComponent<Transform>();
		// La posición y velocidad del nuevo asteroide seran iguales a las del que proviene
		Vector2D p = as_tr->getPos();
		Vector2D v = as_tr->getVel();
		int w= as_tr->getW();
		// Se calcula su tamaño en base a las divisiones restantes
		auto size = 10.0f + 5.0f * gen;
		// Se calcula la rotación de forma aleatoria
		int r = sdlutils().rand().nextInt(0, 360);
		asteroide->addComponent<Transform>(p + v.rotate(r) * 2 * w, v.rotate(r) * 1.1f, size, size, 0.0f);
		// Se podrá dividir una vez menos que su predecesor
		asteroide->addComponent<Generations>(gen-1);
		asteroide->addComponent<ShowAtOppositeSide>();
		// Si el antiguo asteroide tenia el componente follow el nuevo tambien lo tendra, y ademas habra que usar el sprite dorado
		if (as->hasComponent<Follow>())
		{
			asteroide->addComponent<Follow>();
			asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroideOro"), 5, 6, 0, 0);
		}
		// Si no lo tenía, al nuevo no se le añade y se usa el sprite de asteroide normal
		else asteroide->addComponent<FramedImage>(&sdlutils().images().at("asteroide"), 5, 6, 0, 0);
		asteroide->setGroup<Asteroids>(true);
		// Se actualiza el numero de asteroides
		numAsteroides++;
	}
	int getNumAsteroides()
	{
		return numAsteroides;
	}
private:
	int numAsteroides = 0; // Numero total de asteroides
	float timer; // Temporizador
};



