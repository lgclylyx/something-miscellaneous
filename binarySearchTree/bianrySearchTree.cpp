#include "binarySearchTree.h"

int main(){
	//CBinarySearchTree<int>* binarySearchTree=new CBinarySearchTree<int>;
	//binarySearchTree->Insert(10);
	//binarySearchTree->Insert(4);
	//binarySearchTree->Insert(7);
	//binarySearchTree->Insert(5);
	//binarySearchTree->Insert(3);
	//CBinarySearchTree<int> binarySearchTreeCopy(*binarySearchTree);
	//CBinarySearchTree<int> binarySearchTreeAssignment=binarySearchTreeCopy;
	//std::cout<<binarySearchTree->FindMin()<<std::endl;
	//std::cout<<binarySearchTree->FindMax()<<std::endl;
	//binarySearchTree->PrintTree();
	//binarySearchTree->Remove(4);
	//binarySearchTree->PrintTree();
	//binarySearchTreeAssignment.PrintTree();
	//binarySearchTreeAssignment.MakeEmpty();
	CBinarySearchTree<int>* binarySearchTree=new CBinarySearchTree<int>;
	binarySearchTree->Insert(10);
	binarySearchTree->Insert(5);
	binarySearchTree->Insert(6);
	binarySearchTree->Insert(3);
	binarySearchTree->Insert(15);
	binarySearchTree->Insert(12);
	binarySearchTree->Insert(18);
	binarySearchTree->LevelOrder();
	system("pause");
	return 0;
}