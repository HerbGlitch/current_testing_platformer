#ifndef HG_NODE_HPP
#define HG_NODE_HPP

namespace hg {
    template <class N_Type>
    struct node {
        N_Type data;
        node<N_Type> *next;

        node(): next(nullptr){}
        node(N_Type data): data(data), next(nullptr){}
        ~node(){ if(next != nullptr){ delete next; } }
    };
}

#endif //HG_NODE_HPP