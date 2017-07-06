#include <iostream>
#include "BinomialQueue.h"
#include <queue>
#include <functional>

int main(){
	BinomialQueue<int> a;
	BinomialQueue<int> b;
	a.Insert(1);
	a.Insert(2);
	b.Insert(3);
	b.Insert(4);
	a.merge(b);
	std::cout<<a.findMin();
	//a.MakeEmpty();
	//b.MakeEmpty();
	a.deleteMin();
	std::priority_queue<int> c;
	c.push(4);
	c.push(3);
	c.push(5);
	std::priority_queue<int,std::vector<int>,std::greater<int> >d;
	d.push(4);
	d.push(3);
	d.push(5);
	system("pause");
	return 0;
}