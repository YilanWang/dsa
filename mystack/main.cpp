#include <iostream>
#include "STACK.h"
#include "use.h"
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
	char *s = "(2+3)*(5-(2-5))";
	//    auto flag=paren(s,0,15);
	//    std::cout<<flag;
	char *rpn = (char*)malloc(1);
	*rpn = '\0';
	float x = evaluate(s, rpn);
	std::cout << x;
	system("pause");

	return 0;
}