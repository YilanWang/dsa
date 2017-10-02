#include <iostream>
#include "STACK.h"
#include "use.h"
//#include "stackuse.cpp"
//#include <sys/types.h>

//void convert(Stack<char> &s, int64_t n, int base) {
//    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
//    while(n>0)
//    {
//        int re=(int)(n%base);
//        s.push(digit[re]);
//        n/=base;
//    }
//}
//
//bool paren(const char exp[],int lo,int hi){
//    Stack<char>s;
//    for(int i=lo;i<=hi;i++)
//        switch (exp[i]){
//            case '(':
//            case '[':
//            case '{':
//                s.push(exp[i]);
//                break;
//            case ')':
//                if((s.empty())||('('!=s.pop()))
//                    return false;
//                break;
//
//            case ']':
//                if((s.empty())||('['!=s.pop()))
//                    return false;
//                break;
//            case '}':
//                if((s.empty())||('{'!=s.pop()))
//                    return false;
//                break;
//            default:
//                break;
//        }
//    return s.empty();
//}
int main() {
    //Stack<int> a;
//    a.push(1);
//    a.push(3);
//    std::cout<<a[1]<<std::endl;
//    Stack<char> s;
//    convert(s,345,16);
//    std::cout<<s.pop();//<<s.pop()<<s.pop();
//    std::cout<<s.pop();std::cout<<s.pop();
//    //std::endl;
    char *s="(2+3)*(5-(2-5))";
//    auto flag=paren(s,0,15);
//    std::cout<<flag;
    char *rpn;
    float x= evaluate(s,rpn);
    std::cout<<x;


    return 0;
}