//
// Created by alan-wang on 17-9-30.
//
#pragma once
#include "vector.cpp"
#ifndef MYSTACK_STACK_H
#define MYSTACK_STACK_H

template <typename T>class Stack:public Vector<T>
{
    //using Vector::size;
    //using Vector::insert;
public:
    void push(T const & e){Vector<T>::insert(Vector<T>::size(),e);}
    T pop(){ return Vector<T>::remove(Vector<T>::size()-1);}
    T& top(){ return (*this)[Vector<T>::size()-1];}
};
#endif //MYSTACK_STACK_H
