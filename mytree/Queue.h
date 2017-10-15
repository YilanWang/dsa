//
// Created by alan-wang on 17-10-7.
//

#ifndef MYTREE_QUEUE_H
#define MYTREE_QUEUE_H

#include "list/list.cpp"


template <typename T>class Queue:public List<T>{
public:
    void enqueue(T const &e){insertAsLast(e);}
    T dequeue(){ return remove(first());}
    T& front(){ return first()->data;}
};
#endif //MYTREE_QUEUE_H
