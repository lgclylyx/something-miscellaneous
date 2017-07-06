#include "myVector.h"
#include <cstdlib>
#include <iostream>

int main(){
	Vector<int> a;
	for(int i=0;i<100;i++)
		a.push_back(i);
	std::cout<<"theSize: "<<a.Size()<<"\n";
	std::cout<<"theCapacity:	"<<a.Capacity()<<"\n";
	std::cout<<"back:	"<<a.back()<<"\n";
	for(Vector<int>::iterator it=a.begin();it!=a.end();it++){
		std::cout<<*it<<"	";
		if(*it%10==9)
			std::cout<<"\n";
	}
	a[0]=100;
	std::cout<<a[0]<<"\n";
	a.pop_back();
	std::cout<<"theSize:	"<<a.Size()<<"\n";
	std::cout<<"theCapacity:	"<<a.Capacity()<<"\n";
	system("pause");
	return 0;
}