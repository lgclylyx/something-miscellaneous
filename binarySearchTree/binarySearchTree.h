#pragma once
#include <cstdlib>
#include <iostream>
#include <list>

template<typename Comparable>
class CBinarySearchTree{
public:
	CBinarySearchTree();
	~CBinarySearchTree();
	CBinarySearchTree(const CBinarySearchTree&);
	const CBinarySearchTree& operator=(const CBinarySearchTree&);

	const Comparable& FindMax()const;
	const Comparable& FindMin()const;
	bool Contains(const Comparable&)const;
	bool IsEmpty()const;
	void PrintTree()const;
	void MakeEmpty();
	void Insert(const Comparable&);
	void Remove(const Comparable&);
	void LevelOrder();
private:
	struct BinaryNode{
		Comparable element;
		BinaryNode* leftChild;
		BinaryNode* rightChild;

		BinaryNode(const Comparable& element,BinaryNode* left,BinaryNode* right):element(element),leftChild(left),rightChild(right){
		}
	};
	BinaryNode* root;

	void Insert(const Comparable& ,	BinaryNode* &);
	void Remove(const Comparable& , BinaryNode* &);
	BinaryNode* FindMin(BinaryNode*)const;
	BinaryNode* FindMax(BinaryNode*)const;
	bool Contains(const Comparable& , BinaryNode*)const;
	void MakeEmpty(BinaryNode* &);
	void PrintTree(BinaryNode*)const;
	BinaryNode* Clone(BinaryNode* )const;
};

template<typename Comparable>
CBinarySearchTree<Comparable>::CBinarySearchTree():root(NULL){

}

template<typename Comparable>
CBinarySearchTree<Comparable>::~CBinarySearchTree(){
	MakeEmpty();
}

template<typename Comparable>
const CBinarySearchTree<Comparable>& CBinarySearchTree<Comparable>::operator=(const CBinarySearchTree<Comparable>& t){
	if(this!=&t){
		MakeEmpty();
		root=Clone(t.root);
	}
	return *this;
}

template<typename Comparable>
CBinarySearchTree<Comparable>::CBinarySearchTree(const CBinarySearchTree<Comparable>& t){
	root=Clone(t.root);
}

template<typename Comparable>
bool CBinarySearchTree<Comparable>::Contains(const Comparable& x,BinaryNode* t)const{
	if(t==NULL)
		return false;
	else if(x < t->element)
		return Contains(x,t->rightChild);
	else if(t->element < x)
		return Contains(x,t->leftChild);
	else
		return true;
}

template<typename Comparable>
bool CBinarySearchTree<Comparable>::Contains(const Comparable& x)const{
	return Contains(x,root);
}

template<typename Comparable> 
void CBinarySearchTree<Comparable>::Insert(const Comparable& x,BinaryNode* & t){
	if(t==NULL)
		t=new BinaryNode(x,NULL,NULL);
	else if(x < t->element)
		Insert(x,t->leftChild);
	else if(t->element < x)
		Insert(x,t->rightChild);
	else
		;
}

template<typename Comparable> 
void CBinarySearchTree<Comparable>::Insert(const Comparable& x){
		Insert(x,root);
}

template<typename Comparable>
void CBinarySearchTree<Comparable>::Remove(const Comparable& x,BinaryNode* &t){
	if(t==NULL)
		return;
	else if(x < t->element)
		Remove(x,t->leftChild);
	else if(t->element < x)
		Remove(x,t->rightChild);
	else if(t->leftChild!=NULL && t->rightChild!=NULL){
		t->element=FindMin(t->rightChild)->element;
		Remove(t->element,t->rightChild);
	}else{
		BinaryNode *oldNode=t;
		t=(t->leftChild!=NULL)?t->leftChild:t->rightChild;
		delete oldNode;
	}
}

template<typename Comparable>
void CBinarySearchTree<Comparable>::Remove(const Comparable& x){
	Remove(x,root);
}

template<typename Comparable>
typename CBinarySearchTree<Comparable>::BinaryNode* CBinarySearchTree<Comparable>::FindMin(BinaryNode* t)const{
	if(t==NULL)
		return NULL;
	if(t->leftChild==NULL)
		return t;
	return FindMin(t->leftChild);
}

template<typename Comparable>
const Comparable& CBinarySearchTree<Comparable>::FindMin()const{
	if(root==NULL)
		std::cerr<<"NULL"<<std::endl;
	return FindMin(root)->element;
}

template<typename Comparable>
typename CBinarySearchTree<Comparable>::BinaryNode* CBinarySearchTree<Comparable>::FindMax(BinaryNode* t)const{
	if(t==NULL)
		return NULL;
	if(t->rightChild==NULL)
		return t;
	return FindMax(t->rightChild);
}

template<typename Comparable>
const Comparable& CBinarySearchTree<Comparable>::FindMax()const{
	if(root==NULL)
		std::cerr<<"NULL"<<std::endl;
	return FindMax(root)->element;
}

template<typename Comparable>
void CBinarySearchTree<Comparable>::PrintTree()const{
	PrintTree(root);
}

template<typename Comparable>
void CBinarySearchTree<Comparable>::PrintTree(BinaryNode* t)const{
	if(t!=NULL){
		PrintTree(t->leftChild);
		std::cout<<t->element<<std::endl;
		PrintTree(t->rightChild);
	}
}

template<typename Comparable>
bool CBinarySearchTree<Comparable>::IsEmpty()const{
	if(root==NULL)
		return true;
	else
		return false;
}

template<typename Comparable>
void CBinarySearchTree<Comparable>::MakeEmpty(BinaryNode* &t){
	if(t!=NULL){
		MakeEmpty(t->leftChild);
		MakeEmpty(t->rightChild);
		delete t;
	}
	t=NULL;
}

template<typename Comparable>
void CBinarySearchTree<Comparable>::MakeEmpty(){
	MakeEmpty(root);
}

template<typename Comparable>
typename CBinarySearchTree<Comparable>::BinaryNode* CBinarySearchTree<Comparable>::Clone(BinaryNode* t)const{
	if(t==NULL)
		return NULL;
	return new BinaryNode(t->element,Clone(t->leftChild),Clone(t->rightChild));
}

template<typename T>
void CBinarySearchTree<T>::LevelOrder(){
	std::list<BinaryNode*> queue;
	if(root!=NULL)
		queue.push_back(root);
	while(!queue.empty()){
		std::cout<<queue.front()->element<<"	";
		if(queue.front()->leftChild!=NULL)
			queue.push_back(queue.front()->leftChild);
		if(queue.front()->rightChild!=NULL)
			queue.push_back(queue.front()->rightChild);
		queue.pop_front();
	}
}