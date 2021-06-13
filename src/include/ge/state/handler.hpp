#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "state.hpp"
#include <hg/base/vector.hpp>
#include <vector>

namespace ge {
    namespace state {
        class Handler {
        public:
            Handler(){}
            ~Handler(){ clearStates(); }

            void update(){ for(State * &state : states){ state->update(); } }
            void render(){ for(State * &state : states){ state->render(); } }

            void addState(State *state, bool removing = true){
                if(removing){ removeState(); }
                states.push_back(state);
            }

            void removeState(){
                if(states.empty()){ return; }
                State *temp = states.at(states.size() - 1);
                states.erase(states.size() - 1);
                delete temp;
            }

            void clearStates(){ states.clear(); }

        private:
            hg::vector<State *> states;
        };
    }
}

#endif // !HANDLER_HPP