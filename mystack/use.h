//
// Created by alan-wang on 17-10-1.
//
#pragma once
#ifndef MYSTACK_USE_H
#define MYSTACK_USE_H
#define N_optr 9

#include <cctype>
#include <cstring>
#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <cmath>
#include "STACK.h"

typedef enum {
    ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
} Operater;
const char pri[N_optr][N_optr] = {
    //  ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE
        '>', '>', '<', '<', '<', '<', '<', '>', '>',
        '>', '>', '<', '<', '<', '<', '<', '>', '>',
        '>', '>', '>', '>', '<', '<', '<', '>', '>',
        '>', '>', '>', '>', '<', '<', '<', '>', '>',
        '>', '>', '>', '>', '>', '<', '<', '>', '>',
        '>', '>', '>', '>', '>', '>', ' ', '>', '>',
        '<', '<', '<', '<', '<', '<', '<', '=', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

void readNumber(char *&p, Stack<float> &stk) {
    stk.push((float) (*p - '0'));
    while (isdigit(*(++p)))
        stk.push(stk.pop() * 10 + (*p - '0'));
    if ('.' != *p)
        return;
    float fraction = 1;
    while (!isdigit(*(++p)))
        stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
}

void append(char *&rpn, float opnd) {
    int n = strlen(rpn);
    char buf[64];

    if (opnd != (float) (int) opnd) //判断opnd是不是浮点数，因为浮点数转换为整形再转换为浮点型会有损失
        sprintf(buf, "%.2f \0", opnd);
    else
        sprintf(buf, "%d \0", (int) opnd);
    rpn = (char *) realloc(rpn, sizeof(char) * (n + strlen(buf) + 1));
    strcat(rpn, buf);
}

void append(char *&rpn, char optr) {
    int n = strlen(rpn);
    rpn = (char *) realloc(rpn, sizeof(char) * (n + 3));
    sprintf(rpn + n, "%c", optr);
    rpn[n + 2] = '\0';
}

Operater optr2rank(char op) {
    switch (op) {
        case '+':
            return ADD;
        case '-':
            return SUB;
        case '*':
            return MUL;
        case '/':
            return DIV;
        case '^':
            return POW;
        case '!':
            return FAC;
        case '(':
            return L_P;
        case ')':
            return R_P;
        case '\0':
            return EOE;
        default:
            exit(-1);
    }
}

char orderBetween(char op1, char op2) {
    return pri[optr2rank(op1)][optr2rank(op2)];
}

float calcu(char &op, float pOnd) {
    pOnd=int(pOnd);
    if (pOnd == 1)
        return 1;
    else
        return pOnd * calcu(op, pOnd - 1);
}

float calcu(float pOnd1, char &op, float pOnd2) {
    if (op == '+')
        return pOnd1 + pOnd2;
    else if (op == '-')
        return pOnd1 - pOnd2;
    else if (op == '*')
        return pOnd1 * pOnd2;
    else if (op == '/')
        if (pOnd2 == 0)
            throw pOnd2;
        else
            return pOnd1 / pOnd2;  //如果被除数是0，返回一个float异常
    else
        return pow(pOnd1,pOnd2);

}


float evaluate(char *s, char *&rpn) {
    Stack<float> opnd;  //存放数字
    Stack<char> optr;   //存放运算符
    optr.push('\0');
    while (!optr.empty()) {
        if (isdigit(*s)) {
            readNumber(s, opnd);
            append(rpn, opnd.top());
        } else
            switch (orderBetween(optr.top(), *s)) {
                case '<':
                    optr.push(*s);
                    s++;
                    break;
                case '=':   //碰到括号
                    optr.pop();
                    s++;
                    break;
                case '>': {
                    char op = optr.pop();
                    append(rpn, op);
                    if ('!' == op) {
                        float pOpnd = opnd.pop();
                        opnd.push(calcu(op, pOpnd));
                    } else {
                        float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
                        opnd.push(calcu(pOpnd1, op, pOpnd2));
                    }
                    break;
                }
                default:
                    exit(-1);
            }   //end switch
    }   //end while
    return opnd.pop();  //最后结果
}


#endif //MYSTACK_USE_H
