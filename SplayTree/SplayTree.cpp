#include "SplayTree.h"

int main(){
	SplayTree<int> a;
	for(int i=7;i>=1;i--){
		a.Insert(i);
	}
	//a.Splay(1);
	//a.Splay(2);
	//a.Splay(3);
	/*a.Insert(1);
	for(int i=32;i>=2;i=i-2)
		a.Insert(i);
	for(int i=31;i>=3;i=i-2)
		a.Insert(i);
	a.Splay(2);
	std::cout<<"Splay(2):	";
	a.InOrder();
	a.Splay(3);
	std::cout<<"\nSplay(3):	";
	a.InOrder();
	a.Splay(4);
	std::cout<<"\nSplay(4):	";
	a.InOrder();
	a.Splay(5);
	std::cout<<"\nSplay(5):	";
	a.InOrder();
	a.Splay(6);
	std::cout<<"\nSplay(6):	";
	a.InOrder();
	a.Splay(7);
	std::cout<<"\nSplay(7):	";
	a.InOrder();
	a.Splay(8);
	std::cout<<"\nSplay(8):	";
	a.InOrder();
	a.Splay(9);
	std::cout<<"\nSplay(9):	";*/
	a.Splay(0);
	a.InOrder();
	a.Remove(4);
	a.MakeEmpty();
	system("pause");
	return 0;
}