#ifndef HG_NODE_HPP
#define HG_NODE_HPP

namespace hg {
    template <class Object>
    struct node {
        Object current;
        node *next = nullptr;

        node(){}
        node(Object current): current(current){}
    };
}

#endif //HG_NODE_HPP