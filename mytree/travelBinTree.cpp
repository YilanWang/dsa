//
// Created by alan-wang on 17-10-6.
//

#include "tree.h"
#include "Queue.h"

//先序
template<typename T, typename VST>
void travPre_R(BinNodePos(T)x, VST &visit) {
    if (!x)
        return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template<typename T, typename VST>
void travPre_I1(BinNodePos(T)x, VST &visit) {
    Stack<BinNodePos(T)> s;  //借助栈
    if (x)   //x有值
        s.push(x);  //入栈
    while (!s.empty()) { //s不为空
        x = s.pop();  //出栈
        visit(x->data); //同时访问x
        if (HasRChild(*x))   //如果有右孩子就右孩子入栈
            s.push(x->rc);
        if (HasLChild(*x))   //有左孩子就入栈，因为栈的LIFO，所以入栈先右后左
            s.push(x->lc);
    }
}

template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePos(T)x, VST &visit, Stack<BinNodePos(T)> &s) {
    //一直沿左向下访问，同时右孩子入栈
    while (x) {
        visit(x->data);
        s.push(x->rc);
        x = x->lc;
    }
}

template<typename T, typename VST>
void travPre_I2(BinNodePos(T)x, VST &visit) {
    Stack<BinNodePos(T)> s;
    while (true) {
        visitAlongLeftBranch(x, visit, s);
        if (s.empty())
            break;
        x = s.pop();
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &visit) {
    switch (rand() % 3) {
        case 1:
            travPre_I1(this, visit);
            break;
        case 2:
            travPre_I2(this, visit);
            break;
        default:
            travPre_R(this, visit);
    }
}


//中序
template<typename T, typename VST>
void travIn_R(BinNodePos(T)x, VST &visit) {
    if (!x)
        return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template<typename T>
static void goAlongLeftBranch(BinNodePos(T)x, Stack<BinNodePos(T)> &s) {
    while (x) {
        //只把左孩子一直入栈，不访问
        s.push(x);
        x = x->lc;
    }
}

template<typename T, typename VST>
void travIn_I1(BinNodePos(T)x, VST &visit) {
    Stack<BinNodePos(T)> s;
    while (true) {
        goAlongLeftBranch(x, s);
        if (s.empty())
            break;
        x = s.pop();
        visit(x->data);
        x = x->rc;
    }
}

template<typename T, typename VST>
void travIn_I2(BinNodePos(T)x, VST &visit) {
    Stack<BinNodePos(T)> s;
    while (true)
        if (x) {
            s.push(x);
            x = x->lc;
        } else if (!s.empty()) {
            x = s.pop();
            visit(x->data);
            x = x->rc;
        } else
            break;
}

template<typename T, typename VST>
void travIn_I3(BinNodePos(T)x, VST &visit) {
    bool backtrack = false;  //回溯标志，观察是否从右子树回溯而来
    while (true)
        if (!backtrack && HasLChild(*x))   //有左子树且不是刚回溯
            x = x->lc;    //继续向左子前进
        else {   //无左子树
            visit(x->data); //访问
            if (HasRChild(*x)) {  //有右孩子，就向右
                x = x->rc;
                backtrack = false;
            } else {
                if (!(x = x->succ()))
                    break;
                backtrack = true;
            }
        }
}

template<typename T>
template<typename VST>
void travIn_I4(BinNodePos(T)x, VST &visit) {
    while (true)
        if (HasLChild(*x))
            x = x->lc;
        else {
            visit(x->data);
            while (!HasRChild(*x))
                if (!(x = x->succ()))
                    return;
                else
                    visit(x->data);
            x = x->rc;
        }
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn(VST &visit) {
    switch (rand() % 5) {
        case 1:
            travIn_I1(this, visit);
            break;
        case 2:
            travIn_I2(this, visit);
            break;
        case 3:
            travIn_I3(this, visit);
            break;
        case 4:
            travIn_I4(this, visit);
            break;
        default:
            travIn_R(this, visit);
    }
}


//后序
template<typename T, typename VST>
void travPost_R(BinNodePos(T)x, VST &visit) {
    if (!x)
        return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template<typename T>
static void gotoHLVFL(Stack<BinNodePos(T)> &s) {//寻找最高左侧可视叶节点
    while (BinNodePos(T)x = s.top())  //检查栈顶
        if (HasLChild(*x)) {
            if (HasRChild(*x))   //同理，栈是LIFO，所以右侧先入栈
                s.push(x->rc);
            s.push(x->lc);
        } else
            s.push(x->rc);
    s.pop();
}

template<typename T, typename VST>
void travPost_I(BinNodePos(T)x, VST &visit) {
    Stack<BinNodePos(T)> s;
    if (x)
        s.push(x);
    while (!s.empty()) {
        if (s.top() != (x->parent))    //栈顶不是父节点，是其右兄
            gotoHLVFL(s);
        x = s.pop();
        visit(x->data);
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost(VST &visit) {
    switch (rand() % 2) {
        case 1:
            travPost_I(this, visit);
            break;
        default:
            travPost_R(this, visit);
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST &visit) {
    Queue<BinNodePos(T)> q;
    q.enqueue(this);
    while (!q.empty()) {
        BinNodePos(T)x = q.dequeue();
        visit(x->data);
        if (HasLChild(*x))
            q.enqueue(x->lc);
        if (HasRChild((*x)))
            q.enqueue(x->rc);
    }
}

