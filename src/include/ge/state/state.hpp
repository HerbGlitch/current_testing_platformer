#ifndef STATE_HPP
#define STATE_HPP

namespace ge {
    struct Data;

    class State {
    public:
        State(Data *data): data(data){}
        virtual ~State(){};

        virtual void update(){};
        virtual void render(){};

    protected:
        Data *data;
    };
}

#endif // !STATE_HPP

#include "handler.hpp"