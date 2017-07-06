#include "Reference-counting.h"
#include <iostream>
using namespace std;
int main(){
	String a("hello,world!");
	String b=a;
	a.print();
	b.print();
	system("pause");
	return 0;
}