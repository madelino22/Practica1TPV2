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
                            state = State::NEWGAME;
                        }
                        else
                        {
                            Entity* jet = entity_->getMngr()->getHandler<Jet>();
                            entity_->getComponent<State>()->changeState(State::RUNNING);
                            jet->addComponent<FighterCtrl>();
                            jet->addComponent<Gun>();
                            //asteoride
                            for (int x = 0; x < 10; x++) {
                                entity_->getComponent<AsteroidsManager>()->generaAsteroide();
                            }
                        }
                    }
            }
        }
    }

private:

};