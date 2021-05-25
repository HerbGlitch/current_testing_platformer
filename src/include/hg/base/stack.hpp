#ifndef HG_STACK_HPP
#define HG_STACK_HPP

#include "node.hpp"

namespace hg {
    template<class Object>
    class stack {
    public:
        stack(){ size = 0; }

        void push(Object object){
            if(size == 0){
                start.current = object;
                size++;
                return;
            }

            node<Object> *temp = &start;
            for(unsigned int i = 0; i < size - 1; i++){
                temp = temp->next;
            }

            temp->next = new node<Object>(object);
            size++;
        }

        Object pop(){
            node<Object> *temp = &start;
            if(size == 1){
                size = 0;
                return start.current;
            }
            for(unsigned int i = 0; i < size - 2; i++) {
                temp = temp->next;
            }
            Object ret = temp->next->current;
            delete temp->next;
            size--;

            return ret;
        }

        unsigned int getSize(){ return size; }

    private:
        node<Object> start;
        unsigned int size;
    };
}

#endif //HG_stack_HPP