//
// Created by alan-wang on 17-10-5.
//
//#pragma once


#ifndef MYTREE_TREE_H
#define MYTREE_TREE_H


#include <cstdlib>
#include "STACK.h"

#define BinNodePos(T) BinNode<T>*   //节点位置
#define stature(p) ((p)?(p)->height:-1)
typedef enum {
    RB_RED, RB_BLACK
} RBColor;

template<typename T>
struct BinNode {

    //成员
    T data;
    BinNodePos(T)parent;
    BinNodePos(T)lc;
    BinNodePos(T)rc;
    int height;
    int npl;
    RBColor color;

    //构造函数
    BinNode() :
            parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RB_RED) {}

    BinNode(T e, BinNodePos(T)p = nullptr, BinNodePos(T)lc = nullptr, BinNodePos(T)rc = nullptr, int h = 0, int l = 1,
            RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

    //操作API
    int size();

    BinNodePos(T)insertAsLC(T const &);

    BinNodePos(T)insertAsRC(T const &);

    BinNodePos(T)succ();

    template<typename VST>
    void travLevel(VST &); //子树层次遍历
    template<typename VST>
    void travPre(VST &);  //先序遍历
    template<typename VST>
    void travIn(VST &);   //中序遍历
    template<typename VST>
    void travPost(VST &); //后序遍历

    //操作符ETC
    bool operator<(BinNode const &bn) { return data < bn.data; }

    bool operator==(BinNode const &bn) { return data == bn.data; }
};
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)
#define uncle(x) (IsLChild(*((x)->parent))?(x)->parent->parent->rc:(x)->parent->parent->lc)
#define FromParentTo(x) (IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))


template <typename T>BinNodePos(T) BinNode<T>::insertAsLC(T const &e) {
    return lc=new BinNode(e,this);
}

template <typename T>BinNodePos(T) BinNode<T>::insertAsRC(T const &e) {
    return rc=new BinNode(e,this);
}

template <typename T>BinNodePos(T) BinNode<T>::succ() {
    BinNodePos(T)s=this;
    if(rc){
        s=rc;
        while (HasLChild(*s))
            s=s->lc;
    } else{
        while (IsRChild(*s))
            s=s->parent;
        s=s->parent;
    }
    return s;
}








#endif //MYTREE_TREE_H
