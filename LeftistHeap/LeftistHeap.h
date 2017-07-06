#pragma once 
#include <cstdlib>

template<typename T>
class LeftistHeap{
private:
	struct LeftistNode{
		T element;
		LeftistNode* left;
		LeftistNode* right;
		int npl;
		LeftistNode(const T& t,LeftistNode* lt=NULL,LeftistNode* rt=NULL,int np=0):element(t),left(lt),right(rt),npl(np){}
	};
	LeftistNode* root;
public:
	LeftistHeap():root(NULL){

	}
	LeftistHeap(const LeftistHeap& rhs){
		root=Clone(rhs.root);
	}
	const LeftistHeap& operator=(const LeftistHeap& rhs){
		if(this==&rhs)
			return *this;
		MakeEmpty(root);
		root=Clone(rhs.root);
	}
	~LeftistHeap(){
		MakeEmpty();
	}
	void MakeEmpty(){
		if(root==NULL)
			return;
		MakeEmpty(root);
	}
	void merge(LeftistHeap& rhs){
		if(this==&rhs)
			return;
		root=merge(root,rhs.root);
		rhs.root=NULL;
	}
	bool IsEmpty()const{
		return root==NULL;
	}
	void Insert(const T& x){
		root=merge(root,new LeftistNode(x));
	}
	void deleteMin(){
		if(!IsEmpty()){
			LeftistNode* t=root;
			root=merge(root->left,root->right);
			delete t;
		}
	}
private:
	LeftistNode* merge(LeftistNode* h1,LeftistNode* h2){
		if(h1==NULL)
			return h2;
		if(h2==NULL)
			return h1;
		if(h2->element<h1->element){//��֤h1��ֵ��С
			LeftistNode* temp=h1;
			h1=h2;
			h2=temp;
		}
		if(h1->right==NULL||h1->right->element<h2->element){//�ҵ�����㣬h1���ֺ���Ϊ�գ��ҷ��϶�������
			h1->right=merge(h1->right,h2);
		}else{
			h1->right=merge(h2,h1->right);
		}
		if(NPL(h1->left)<NPL(h1->right))//�����ʽ�����ʱ��ƻ����򽻻���������
			swapChildren(h1);
		h1->npl=NPL(h1->right)+1;//���½ڵ�NPL
		return h1;
	}
	void swapChildren(LeftistNode* h1){
		if(h1==NULL)
			return;
		LeftistNode* t=h1->left;
		h1->left=h1->right;
		h1->right=t;
	}
	int NPL(LeftistNode* t)const{
		return t==NULL?-1:t->npl;
	}
	void MakeEmpty(LeftistNode*& t){
		if(t!=NULL){
			MakeEmpty(t->left);
			MakeEmpty(t->right);
			delete t;
		}
		t=NULL;
	}
	LeftistNode* Clone(LeftistNode* t)const{
		if(t==NULL)
			return t;
		return new LeftistNode(t->element,Clone(t->left),Clone(t->right),t->npl);
	}
};