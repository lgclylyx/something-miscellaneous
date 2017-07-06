#include "proxy-String.h"

int main(){
	String a;
	a="hello,world!";
	String b(a);
	b[2]='a';
	b[3]=a[0];
	return 0;
}