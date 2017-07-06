#include "SkewHeap.h"

int main(){
	SkewHeap<int> a;
	SkewHeap<int> b;
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
	a.Print();
	std::cout<<"\n";
	b.Print();
	std::cout<<"\n";
	a.deleteMin();
	b.deleteMin();
	a.Print();
	std::cout<<"\n";
	b.Print();
	std::cout<<"\n";
	system("pause");
	return 0;
}