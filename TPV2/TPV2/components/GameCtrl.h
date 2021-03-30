#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "State.h"
#include "AsteroidsManager.h"


class GameCtrl : public Component {
public:
    GameCtrl() 
    {
    }
    virtual ~GameCtrl() {
    }

    

    void update() override {
        if (ih().keyDownEvent()) {
            // Al pulsar la tecla espacio se actualiza el estado actual
             if (ih().isKeyDown(SDL_SCANCODE_SPACE)) { 

                State* state = entity_->getComponent<State>();
                
                    //si se está en un estado distinto de running, es decir en un menú, y se ha pulsado espacio
                    if (state->getState() != State::RUNNING)
                    {
                        if (state->getState() == State::GAMEOVER || state->getState() == State::WON)
                        {
                            //al ganar o perder hay que poner las vidas como al principio de la partida
                            entity_->getMngr()->getHandler<Jet>()->getComponent<Health>()->resetLives();
                            //una vez restablecidos los valor se cambia el estado a pausa
                            state->changeState(State::PAUSED);
                        }
                        else
                        {
                            // Si el estado es NEWGAME o PAUSED habrá que añadir los componentes de accion al caza para que se pueda volver a jugar
                            Entity* jet = entity_->getMngr()->getHandler<Jet>();                            
                            jet->addComponent<FighterCtrl>();
                            jet->addComponent<Gun>();
                            // Ademas, generamos los diez asteroides iniciales
                            for (int x = 0; x < 10; x++) {
                                entity_->getComponent<AsteroidsManager>()->generaAsteroide();
                            }
                            // Pasamos a RUNNING
                            state->changeState(State::RUNNING);
                        }
                    }
            }
        }
    }
};