#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "state.hpp"
#include <vector>
#include <iostream>

namespace ge {
    namespace state {
        class Handler {
        public:
            Handler(){}
            ~Handler(){ clearStates(); }

            void update(){
                if(!deleteQueue.empty()){
                    for(State *state : deleteQueue){ delete state; }
                    deleteQueue.clear();
                }
                for(State *state : states){ state->update(); }
            }
            void render(){ for(State *state : states){ state->render(); } }

            void addState(State *state, bool removing = true){
                if(removing){ removeState(); }
                states.push_back(state);
            }

            void removeState(){
                if(states.empty()){ return; }
                deleteQueue.push_back(states.at(states.size() - 1));
                states.erase(states.begin() + states.size() - 1);
            }

            void clearStates(){
                for(State *state : states){ delete state; }
                states.clear();
            }

        private:
            std::vector<State *> states;
            std::vector<State *> deleteQueue;
        };
    }
}

#endif // !HANDLER_HPP