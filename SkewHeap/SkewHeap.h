#pragma once
#include <list>
#include <iostream>

template<typename T>
class SkewHeap{
private:
	struct SkewNode{
		T element;
		SkewNode* left;
		SkewNode* right;
		SkewNode(const T& t,SkewNode* lp=NULL,SkewNode* rp=NULL):element(t),left(lp),right(rp){}
	};
	SkewNode* root;
public:
	SkewHeap():root(NULL){}
	~SkewHeap(){
		MakeEmpty(root);
	}
	SkewHeap(const SkewHeap& rhs){
		root=Clone(rhs.root);
	}
	const SkewHeap& operator=(const SkewHeap& rhs){
		if(this==&rhs)
			return *this;
		MakeEmpty();
		root=Clone(rhs.root);
		return *this;
	}
	void merge(SkewHeap& rhs){
		if(this==&rhs)
			return;
		root=merge(root,rhs.root);
		rhs.root=NULL;
	}
	void Insert(const T& x){
		root=merge(root,new SkewNode(x));
	}
	void deleteMin(){
		if(root!=NULL){
			SkewNode* temp=root;
			root=merge(root->left,root->right);
			delete temp;
		}
	}
	bool IsEmpty()const{
		return root==NULL;
	}
	void MakeEmpty(){
		MakeEmpty(root);
	}
	void Print(){
		std::list<SkewNode*> queue;
		queue.push_back(root);
		while(!queue.empty()){
			SkewNode* temp=queue.front();
			std::cout<<temp->element<<"	";
			if(temp->left!=NULL)
				queue.push_back(temp->left);
			if(temp->right!=NULL)
				queue.push_back(temp->right);
			queue.pop_front();
		}
	}
private:
	SkewNode* merge(SkewNode* h1,SkewNode* h2){
		if(h1==NULL)
			return h2;
		if(h2==NULL)
			return h1;
		if(h2->element<h1->element)
			Swap(h1,h2);
		if(h1->right==NULL||h1->right->element<h2->element)
			h1->right=merge(h1->right,h2);
		else
			h1->right=merge(h2,h1->right);
		Swap(h1->left,h1->right);
		return h1;
	}
	template<typename P>
	void Swap(P& x,P& y){
		P temp=x;
		x=y;
		y=temp;
	}
	void MakeEmpty(SkewNode*& t){
		if(!IsEmpty()){
			MakeEmpty(t->left);
			MakeEmpty(t->right);
			delete t;
		}
		t=NULL;
	}
	SkewNode* Clone(SkewNode* t){
		if(t==NULL)
			return NULL;
		return new SkewNode(t->element,Clone(t->left),Clone(t->right));
	}
};