#include <iostream>
#include "AVLTree.h"

static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};

int main(){
	AVLTree<int> a;
	std::cout << "== �������: ";
	int ilen=sizeof(arr)/sizeof(arr[0]);
	for(int i=0; i<ilen; i++){
		std::cout << arr[i] <<" ";
		a.Insert(arr[i]);
	}
	std::cout << "\n== ǰ�����: ";
	a.PreOrder();
	std::cout << "\n== �������: ";
	a.InOrder();
	std::cout << "\n== �������: ";
	a.PostOrder();
	std::cout <<std::endl;
	std::cout << "\n== ɾ�����ڵ�: " <<8;
	a.Remove(8);
	a.Remove(12);
	std::cout << "\n== �߶�: " << a.height() ;
	std::cout << "\n== �������: " ;
	a.InOrder();
	a.MakeEmpty();
	system("pause");
	return 0;
}