#pragma once
//splay tree from bottom to top
#include <cstdlib>
#include <iostream>

template<typename T>
class SplayTree{
private:
	struct SplayTreeNode{
		T data;
		SplayTreeNode* lChild;
		SplayTreeNode* rChild;
		SplayTreeNode* pParent;
		SplayTreeNode(const T& t,SplayTreeNode* pP=NULL,SplayTreeNode* lc=NULL,SplayTreeNode* rc=NULL):data(t),pParent(pP),lChild(lc),rChild(rc){}
	};
public:
	SplayTree():root(NULL){}
	~SplayTree(){
		MakeEmpty();
	}
	void Insert(const T& x){
		Insert(x,root);
	}
	void Splay(const T& x){
		Splay(x,root);
	}
	void InOrder()const{
		InOrder(root);
	}
	bool IsEmpty()const{
		return root==NULL;
	}
	void Remove(const T& x){
		if(root==NULL)
			return;
		SplayTreeNode* temp;
		Splay(x,root);
		temp=root;
		if(root->data!=x)
			return;
		if(root->lChild!=NULL){
			root=root->lChild;
			root->pParent=NULL;
			Splay(x,root);
			root->rChild=temp->rChild;
			if(root->rChild!=NULL)
				root->rChild->pParent=root;
		}else{
			root=root->rChild;
			if(root!=NULL)
				root->pParent=NULL;
		}
		delete temp;
	}
	void MakeEmpty(){
		while(!IsEmpty()){
			Remove(root->data);
		}
	}
private:
	SplayTree(const SplayTree& rhs);
	const SplayTree& operator=(const SplayTree& rhs);
	void Insert(const T& x,SplayTreeNode*& t,SplayTreeNode* pP=NULL){
		if(t==NULL)
			t=new SplayTreeNode(x,pP);
		if(x<t->data)
			Insert(x,t->lChild,t);
		else if(t->data<x)
			Insert(x,t->rChild,t);
		else
			;
	}
	void Splay(const T& x,SplayTreeNode* t){
		if(t==NULL)
			return;
		while(true){
			if(x<t->data){
				if(t->lChild==NULL)
					break;
				t=t->lChild;
			}
			else if(t->data<x){
				if(t->rChild==NULL)
					break;
				t=t->rChild;
			}
			else
				break;
		}
		while(true){
			if(t->pParent==NULL)
				break;
			else if(t->pParent->pParent==NULL){
				if(t->pParent->lChild==t)
					RotationWithLeftChild(t->pParent);
				else 
					RotationWithRightChild(t->pParent);
			}else if(t==t->pParent->lChild&&t->pParent->pParent->lChild==t->pParent){
				RotationWithLeftChild(t->pParent->pParent);
				RotationWithLeftChild(t->pParent);
			}else if(t==t->pParent->rChild&&t->pParent->pParent->lChild==t->pParent){
				RotationWithRightChild(t->pParent);
				RotationWithLeftChild(t->pParent);
			}else if(t==t->pParent->lChild&&t->pParent->pParent->rChild==t->pParent){
				RotationWithLeftChild(t->pParent);
				RotationWithRightChild(t->pParent);
			}else if(t==t->pParent->rChild&&t->pParent->pParent->rChild==t->pParent){
				RotationWithRightChild(t->pParent->pParent);
				RotationWithRightChild(t->pParent);
			}
		}
		root=t;
	}
	void RotationWithLeftChild(SplayTreeNode* k2){
		SplayTreeNode* k1=k2->lChild;
		k2->lChild=k1->rChild;
		if(k1->rChild!=NULL)
			k1->rChild->pParent=k2;
		k1->pParent=k2->pParent;
		k1->rChild=k2;
		if(k2->pParent!=NULL)
			if(k2->pParent->lChild==k2)
				k2->pParent->lChild=k1;
			else
				k2->pParent->rChild=k1;
		k2->pParent=k1;
	}
	void RotationWithRightChild(SplayTreeNode* k2){
		SplayTreeNode* k1=k2->rChild;
		k2->rChild=k1->lChild;
		if(k1->lChild!=NULL)
			k1->lChild->pParent=k2;
		k1->pParent=k2->pParent;
		k1->lChild=k2;
		if(k2->pParent!=NULL)
			if(k2->pParent->lChild==k2)
				k2->pParent->lChild=k1;
			else
				k2->pParent->rChild=k1;
		k2->pParent=k1;
	}
	void InOrder(SplayTreeNode* t)const{
		if(t!=NULL){
			InOrder(t->lChild);
			InOrder(t->rChild);
			std::cout<<t->data<<"	";
		}
	}
	SplayTreeNode* root;
};