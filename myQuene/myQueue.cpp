#include "myQueue.h"
#include "myQueueList.h"

#include <iostream>

int main(){
	/*myQueue<int> a(10);*/
	myQueueList<int> a;
	if(a.IsEmpty()){
		for(int i=0;i<9;i++)
			a.Enqueue(i);
		for(int i=0;i<9;i++)
			std::cout<<a.Dequeue()<<"	";
	}
	if(a.IsEmpty())
		std::cout<<"\n";
	/*myQueue<int> b(a);*/
	myQueueList<int> b(a);
	myQueueList<int> c;
	if(b.IsEmpty()){
		for(int i=0;i<9;i++)
			b.Enqueue(i);
		c=b;
		for(int i=0;i<9;i++)
			std::cout<<b.Dequeue()<<"	";
	}
	if(b.IsEmpty())
		std::cout<<"\n";
	for(int i=0;i<9;i++)
		std::cout<<c.Dequeue()<<"	";
	if(c.IsEmpty())
		std::cout<<"\n";
	system("pause");
	return 0;
}