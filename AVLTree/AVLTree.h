#pragma once
#include <algorithm>
#include <iostream>

template<typename T>
class AVLTree{
private:
	struct AVLNode{
		T data;
		AVLNode* lChild;
		AVLNode* rChild;
		int height;
		AVLNode(const T& t,AVLNode* lc=NULL,AVLNode* rc=NULL,int h=0):data(t),lChild(lc),rChild(rc),height(h){}
	};
public:
	AVLTree():root(NULL){}
	AVLTree(const AVLTree& rhs){
		root=Clone(rhs.root);
	}
	const AVLTree& operator=(const AVLTree& rhs){
		if(this==&rhs)
			return *this;
		MakeEmpty();
		root=Clone(rhs.root);
		return *this;
	}
	~AVLTree(){
		MakeEmpty();
	}
	void Insert(const T& x){
		Insert(x,root);
	}
	void Remove(const T& x){
		Remove(x,root);
	}
	const T& FindMin()const{
		if(root==NULL)
			std::cerr<<"empty tree"<<std::endl;
		return FindMin(root)->data;
	}
	const T& FindMax()const{
		if(root==NULL)
			std::cerr<<"empty tree"<<std::endl;
		return FindMax(root)->data;
	}
	void MakeEmpty(){
		MakeEmpty(root);
	}
	bool IsEmpty()const{
		return root==NULL;
	}
	void PreOrder()const{
		PreOrder(root);
	}
	void InOrder()const{
		InOrder(root);
	}
	void PostOrder()const{
		PostOrder(root);
	}
	int height()const{
		return height(root);
	}
private:
	void Insert(const T& x,AVLNode*& t){
		if(t==NULL)
			t=new AVLNode(x);
		else if(x<t->data){
			Insert(x,t->lChild);
			if(height(t->lChild)-height(t->rChild)==2)
				if(x<t->lChild->data)
					RotationWithLeftChild(t);
				else
					DoubleRotationWithRightChild(t);
		}
		else if(t->data<x){
			Insert(x,t->rChild);
			if(height(t->rChild)-height(t->lChild)==2)
				if(t->rChild->data<x)
					RotationWithRightChild(t);
				else
					DoubleRotationWithLeftChild(t);
		} 
		t->height=std::max(height(t->lChild),height(t->rChild))+1;
	}
	void RotationWithLeftChild(AVLNode*& k2){
		AVLNode* k1=k2->lChild;
		k2->lChild=k1->rChild;
		k1->rChild=k2;
		k2->height=std::max(height(k2->lChild),height(k2->rChild))+1;
		k1->height=std::max(height(k1->lChild),k2->height)+1;
		k2=k1;
	}
	void DoubleRotationWithLeftChild(AVLNode*& k3){
		RotationWithLeftChild(k3->rChild);
		RotationWithRightChild(k3);
	}
	void RotationWithRightChild(AVLNode*& k2){
		AVLNode* k1=k2->rChild;
		k2->rChild=k1->lChild;
		k1->lChild=k2;
		k2->height=std::max(height(k2->lChild),height(k2->rChild))+1;
		k1->height=std::max(height(k1->rChild),k2->height)+1;
		k2=k1;
	}
	void DoubleRotationWithRightChild(AVLNode*& k3){
		RotationWithRightChild(k3->lChild);
		RotationWithLeftChild(k3);
	}
	void Remove(const T& x,AVLNode*& t){
		if(t==NULL)
			return;
		else if(x<t->data){
			Remove(x,t->lChild);
			if(height(t->lChild)-height(t->rChild)==2)
				if(height(t->rChild->lChild)<height(t->rChild->rChild))
					RotationWithRightChild(t);
				else
					DoubleRotationWithLeftChild(t);
		}else if(t->data<x){
			Remove(x,t->rChild);
			if(height(t->lChild)-height(t->rChild)==2)
				if(height(t->lChild->lChild)<height(t->lChild->rChild))
					DoubleRotationWithRightChild(t);
				else
					RotationWithLeftChild(t);
		}else if(t->lChild!=NULL&&t->rChild!=NULL){
			if(height(t->lChild)>height(t->rChild)){
				t->data=FindMax(t->lChild)->data;
				Remove(t->data,t->lChild);
			}else{
				t->data=FindMin(t->rChild)->data;
				Remove(t->data,t->rChild);
			}
		}else{
			AVLNode* oldNode=t;
			t=(t->lChild!=NULL)?t->lChild:t->rChild;
			delete oldNode;
		}
		if(t!=NULL)
			t->height=std::max(height(t->lChild),height(t->rChild))+1;
	}
	AVLNode* FindMin(AVLNode* t)const{
		if(t==NULL)
			return NULL;
		if(t->lChild==NULL)
			return t;
		return FindMin(t->lChild);
	}
	AVLNode* FindMax(AVLNode* t)const{
		if(t==NULL)
			return NULL;
		if(t->rChild==NULL)
			return t;
		return FindMax(t->rChild);
	}
	void MakeEmpty(AVLNode* & t){
		if(t!=NULL){
			MakeEmpty(t->lChild);
			MakeEmpty(t->rChild);
			delete t;
		}
		t=NULL;
	}
	void PreOrder(AVLNode* t)const{
		if(t!=NULL){
			std::cout<<t->data<<" ";
			PreOrder(t->lChild);
			PreOrder(t->rChild);
		}
	}
	void InOrder(AVLNode* t)const{
		if(t!=NULL){
			InOrder(t->lChild);
			std::cout<<t->data<<" ";
			InOrder(t->rChild);
		}
	}
	void PostOrder(AVLNode* t)const{
		if(t!=NULL){
			PostOrder(t->lChild);
			PostOrder(t->rChild);
			std::cout<<t->data<<" ";
		}
	}
	AVLNode* Clone(AVLNode* t)const{
		if(t==NULL)
			return NULL;
		return new AVLNode(t->data,Clone(t->lChild),Clone(t->rChild),t->height);
	}
	int height(AVLNode* t)const{
		return t==NULL?-1:t->height;
	}
	AVLNode* root;
};