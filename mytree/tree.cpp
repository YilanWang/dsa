//
// Created by alan-wang on 17-10-5.
//

#include "tree.h"
#include <algorithm>
template <typename T>class BinTree{
protected:
    int _size;
    BinNodePos(T) _root;
    virtual int updateHeight(BinNodePos(T)x);
    void updateHeightAbove(BinNodePos(T)x);

public:
    BinTree():_size(0),_root(nullptr){}
    ~BinTree(){if(0<_size)remove(_root);}
    int size()const { return _size;}
    bool empty()const { return !_root;}
    BinNodePos(T) root() const { return _root;}
    BinNodePos(T) insertAsRoot(T const& e);
    BinNodePos(T) insertAsLC(BinNodePos(T) x,T const& e);
    BinNodePos(T) insertAsRC(BinNodePos(T) x,T const& e);
    BinNodePos(T) attachAsLC(BinNodePos(T) x,BinTree<T>*&T);    //x作为左子树接入
    BinNodePos(T) attachAsRC(BinNodePos(T) x,BinTree<T>*&T);
    int remove(BinNodePos(T)x); //删除x子树，返回子树规模
    BinTree<T>* secede(BinNodePos(T)x); //x子树摘除作为一个独立子树
    template <typename VST>void travLevel(VST& visit){if (_root)_root->traLevel(visit);}
    template <typename VST>void travPre(VST& visit){if (_root)_root->travPre(visit);}
    template <typename VST>void travIn(VST& visit){if (_root)_root->travIn(visit);}
    template <typename VST>void travPost(VST& visit){if (_root)_root->travPost(visit);}
    bool operator<(BinTree<T> const&t) {
        return _root&&t._root&&lt(_root,t._root);}
    bool lt(BinNodePos(T)& root1,BinNodePos(T)& root2){
        return (root1->data<root2->data);
    }
    bool operator==(BinTree<T> const&t){
        return _root&&t._root&&(_root==t._root);
    }
};

template <typename T>int BinTree<T>::updateHeight(BinNodePos(T) x) {
    return x->height=1+std::max(stature(x->lc),stature(x->rc));
}


template <typename T>void BinTree<T>::updateHeightAbove(BinNode<T> *x) {
    while (x){
        updateHeight(x);
        x=x->parent;
    }
}

template <typename T>BinNodePos(T) BinTree<T>::insertAsRoot(T const &e) {
    _size=1;
    return _root=new BinNode<T> (e);
}

template <typename T>BinNodePos(T) BinTree<T>::insertAsLC(BinNode<T> *x, T const &e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template <typename T>BinNodePos(T) BinTree<T>::insertAsRC(BinNode<T> *x, T const &e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template <typename T>BinNodePos(T)  BinTree<T>::attachAsLC(BinNode<T> *x, BinTree<T> *&s) {
    //这个函数是把子树s当做节点x的左子树接入
    if(x->lc=s->_root)
        x->lc->parent=x;
    _size+=s->_size;
    updateHeightAbove(x);
    s->_root=NULL;
    s->_size=0;
    release(s);
    s= nullptr;
    return x;
}

template <typename T>BinNodePos(T) BinTree<T>::attachAsRC(BinNode<T> *x, BinTree<T> *&s) {
    if (x->rc=s->_root)
        x->rc->parent=x;
    _size+=s->_size;
    updateHeightAbove(x);
    s->_root=NULL;
    s->_size=0;
    release(s);
    s= nullptr;
    return x;
}

template <typename T>int BinTree<T>::remove(BinNode<T> *x) {
    FromParentTo(*x)=NULL;
    updateHeightAbove(x->parent);
    int n=removeAt(x);
    _size-=n;
    return n;
}

