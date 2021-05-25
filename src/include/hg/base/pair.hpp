#ifndef HG_PAIR_HPP
#define HG_PAIR_HPP

namespace hg {
    template <class First, class Second>
    struct pair {
        First first;
        Second second;

        pair(){}
        pair(First first, Second second): first(first), second(second){}
    };
}

#endif //HG_PAIR_HPP