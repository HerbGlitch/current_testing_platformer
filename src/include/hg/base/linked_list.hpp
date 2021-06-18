#ifndef HB_LINKED_LIST_HPP
#define HB_LINKED_LIST_HPP

#include "node.hpp"

namespace hg {
    template <class V_Type>
    class linked_list {
    public:
        struct iterator {
            node<V_Type> *iter;

            iterator(node<V_Type> *iter): iter(iter){}

            void operator++(){ iter = iter->next; }
            bool operator!=(iterator &other){ return other.iter != iter; }
            V_Type &operator*(){ return iter->data; }
        };


        linked_list(): n(nullptr), height(0){}
        ~linked_list(){ clear(); }

        void push_back(V_Type data){
            if(height == 0){
                n = new node<V_Type>(data);
                height++;
                return;
            }
            node<V_Type> *iter = node_at(height - 1);
            iter->next = new node<V_Type>(data);
            height++;
        }

        void erase(int index){
            if(index < 0){ return; }
            erase((unsigned int) index);
        }

        void erase(unsigned int index){
            if(index < 0 && index > height - 1){ return; }

            node<V_Type> *temp;
            if(index == 0){
                temp = n;
                n = (height == 1)? nullptr : n->next;
                temp->next = nullptr;
                delete temp;
                height--;
                return;
            }

            node<V_Type> *iter = node_at(index - 1);
            temp = iter->next;
            iter->next = (index == height - 1)? nullptr : iter->next->next;
            temp->next = nullptr;
            delete temp;
            height--;
        }

        void clear(){
            delete n;
            height = 0;
        }

        V_Type &at(int index)         { return node_at(index)->data; }
        V_Type &at(unsigned int index){ return node_at(index)->data; }

        unsigned int size(){ return height; }
        bool empty(){ return height == 0; }

        iterator begin(){ return iterator(n); }
        iterator end(){ return iterator(node_at(height - 1)->next); }

    private:
        node<V_Type> *node_at(unsigned int index){
            node<V_Type> *iter = n;
            for(unsigned int i = 0; i < index; i++){ iter = iter->next; }
            return iter;
        }

        node<V_Type> *n;
        unsigned int height;
    };
}

#endif