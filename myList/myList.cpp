#include "myList.h"
#include "myListLazyDelete.h"
#include <iostream>

int main(){
	//myList<int> a;
	//for(int i=0;i<100;i++)
	//	a.push_back(i);
	//std::cout<<"theSize:	"<<a.Size()<<"\n";
	//for(myList<int>::iterator itr=a.begin();itr!=a.end();++itr){
	//	std::cout<<*itr<<"	";
	//	if(*itr%10==9)
	//		std::cout<<"\n";
	//}
	//a.clear();
	//std::cout<<"theSize:	"<<a.Size()<<"\n";
	//for(int i=0;i<100;i++)
	//	a.push_back(i);
	//std::cout<<"theSize:	"<<a.Size()<<"\n";
	//std::cout<<"front:	"<<a.front()<<"\n";
	//std::cout<<"back:	"<<a.back()<<"\n";
	//a.pop_back();
	//a.pop_front();
	//std::cout<<"theSize:	"<<a.Size()<<"\n";
	//std::cout<<"front:	"<<a.front()<<"\n";
	//std::cout<<"back:	"<<a.back()<<"\n";
	//myList<int> b=a;
	//b=a;
	myListLazyDelete<int> a;
	for(int i=0;i<10;i++)
		a.Push_Back(i);
	myListLazyDelete<int> b(a);
	myListLazyDelete<int> c;
	c=b;
	std::cout<<"theSize:	"<<a.Size()<<"\n";
	//a.Erase(a.Begin());
	//a.Erase(--a.End());
	a.Pop_Back();
	a.Pop_Front();
	for(myListLazyDelete<int>::iterator itr=a.Begin();itr!=a.End();++itr){
		std::cout<<*itr<<"	";
		if(*itr%10==9)
			std::cout<<"\n";
	}
	std::cout<<a.Front()<<"\n";
	std::cout<<a.Back()<<"\n";
	std::cout<<"theSize:	"<<a.Size()<<"\n";
	a.Erase(++a.Begin(),--a.End());
	std::cout<<"theSize:	"<<a.Size()<<"\n";
	for(myListLazyDelete<int>::iterator itr=a.Begin();itr!=a.End();++itr){
		std::cout<<*itr<<"	";
		if(*itr%10==9)
			std::cout<<"\n";
	}
	a.clear();
	std::cout<<"theSize:	"<<a.Size()<<"\n";
	system("pause");
	return 0;
}