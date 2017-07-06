#include "BinaryHeap.h"

int main(){
	BinaryHeap<int> a;
	//for(int i=21;i>=1;i--)
	//	a.Insert(i);
	//a.print();
	//a.deleteMin();
	//a.print();
	std::vector<int> b;
	b.push_back(10);
	b.push_back(12);
	b.push_back(1);
	b.push_back(14);
	b.push_back(6);
	b.push_back(5);
	b.push_back(8);
	b.push_back(15);
	b.push_back(3);
	b.push_back(9);
	b.push_back(7);
	b.push_back(4);
	b.push_back(11);
	b.push_back(13);
	b.push_back(2);
	for(int i=0;i<b.size();i++)
		a.Insert(b[i]);
	a.deleteMin();
	a.deleteMin();
	a.deleteMin();
	a.print();
	BinaryHeap<int> c(b);
	c.deleteMin();
	c.deleteMin();
	c.deleteMin();
	c.print();
	system("pause");
	return 0;
}