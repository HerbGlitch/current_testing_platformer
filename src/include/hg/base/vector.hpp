#ifndef HB_VECTOR_HPP
#define HB_VECTOR_HPP

#include "node.hpp"

namespace hg {
    template <class T>
    class vector {
    public:
        T data;
        vector<T> *node;
        int height;

        vector(): node(nullptr), height(0){}
        vector(T data): data(data), height(0){}

        ~vector<T>(){ if(node != nullptr){ delete node; } }

        void push_back(T data){
            if (height == 0) {
                this->data = data;
                height = 1;
                return;
            }
            vector<T>* iter = this;
            for (int i = 1; i < height; i++){ iter = iter->node; }
            iter->node = new vector<T>(data);
            height++;
        }

        T &at(int index){
            vector<T> *iter = this;
            for(int i = 0; i < index; i++){
                if(iter == nullptr){ return iter->data; }
                iter = iter->node;
            }
            return iter->data;
        }

        void erase(int index){
            index++;
            if(index < 1 && index > height - 1){ return; }
            vector<T> *prev, *iter = this;
            for(int i = 0; i < index; i++){
                prev = iter;
                iter = iter->node;
            }
            prev->node = iter->node;
            delete iter;
        }

        int size(){ return height; }

        bool empty(){ return height == 0; }

        T *begin(){ return &data; }
        T *end(){
            vector<T> *iter = node;
            for(int i = 1; i < height - 1; i++){ iter = iter->node; }
            return &iter->data;
        }

        void clear(){
            vector* iter = node;
            if (iter != nullptr) {
                vector* temp = iter->node;
                delete iter;
                iter = temp;
            }
        }
    };
}

#endif