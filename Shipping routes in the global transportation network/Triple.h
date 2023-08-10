//
// Created by merom on 5/31/2023.
//

#ifndef HOMEWORK2_V2_DEADLINE_04_06_23_TRIPLE_H
#define HOMEWORK2_V2_DEADLINE_04_06_23_TRIPLE_H
template<class T, class W, class X>
struct Triple{
    Triple():_first(),_second(),_third(){}
    Triple(const T &t, const W & w, const X &x):_first(t),_second(w),_third(x){}
    T _first;
    W _second;
    X _third;
};

#endif //HOMEWORK2_V2_DEADLINE_04_06_23_TRIPLE_H
