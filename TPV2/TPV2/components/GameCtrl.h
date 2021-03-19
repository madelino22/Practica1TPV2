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
             if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {

                State::States state = entity_->getComponent<State>()->getState();
                
                    if (state != State::RUNNING)
                    {
                        if (state == State::GAMEOVER)
                        {
                            entity_->getMngr()->getHandler<Jet>()->getComponent<Health>()->resetLives();
                            state = State::NEWGAME;
                        }
                        else
                        {
                            Entity* jet = entity_->getMngr()->getHandler<Jet>();                            
                            jet->addComponent<FighterCtrl>();
                            jet->addComponent<Gun>();
                            //asteoride
                            for (int x = 0; x < 10; x++) {
                                entity_->getComponent<AsteroidsManager>()->generaAsteroide();
                            }
                            state = State::RUNNING;
                        }
                    }
            }
        }
    }

private:

};