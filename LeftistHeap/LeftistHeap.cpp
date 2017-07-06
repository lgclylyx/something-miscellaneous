#include "LeftistHeap.h"

int main(){
	LeftistHeap<int> a;
	LeftistHeap<int> b;
	a.Insert(2);
	a.Insert(5);
	a.Insert(18);
	a.Insert(7);
	a.Insert(3);
	b.Insert(6);
	b.Insert(12);
	b.Insert(7);
	b.Insert(37);
	b.Insert(33);
	b.Insert(24);
	a.deleteMin();
	b.deleteMin();
	LeftistHeap<int> c;
	for(int i=1;i<=15;i++)
		c.Insert(i);
	system("pause");
	return 0;
}