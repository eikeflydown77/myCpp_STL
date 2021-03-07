//
// Created by 龚世炎 on 2021/2/13.
//

#ifndef STACK_H
#define STACK_H
#include "Vector.h"

template <typename T>
class Stack : public Vector<T>{
public:
    void push(T const &e) {insert(Vector<T>::size(), e);}   //入栈
    T & pop() {return remove(Vector<T>::size() - 1);}   //出栈
    T & top() {return (*this)[Vector<T>::size() - 1];}     //取顶
};


#endif //STACK_H
