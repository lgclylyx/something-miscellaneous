#pragma once
#include <vector>

template<typename T>
class BinomialQueue{
private:
	struct BinomialNode{
		T element;
		BinomialNode* leftChild;
		BinomialNode* nextSibling;
		BinomialNode(const T& t,BinomialNode* lt=NULL,BinomialNode* rt=NULL):element(t),leftChild(lt),nextSibling(rt){}
	};
	int currentSize;
	std::vector<BinomialNode*> theTree;
public:
	BinomialQueue():currentSize(0){

	}
	BinomialQueue(const T& x){
		currentSize=1;
		theTree.push_back(new BinomialNode(x));
	}
	BinomialQueue(const BinomialQueue& rhs){
		currentSize=rhs.currentSize;
		for(int i=0;i<rhs.theTree.size();i++){
			theTree[i]=Clone(rhs.theTree[i]);
		}
	}
	const BinomialQueue& operator=(const BinomialQueue& rhs){
		if(this==&rhs)
			return *this;
		MakeEmpty();
		currentSize=rhs.currentSize;
		for(int i=0;i<rhs.theTree.size();i++){
			theTree[i]=Clone(rhs.theTree[i]);
		}
		return *this;
	}
	~BinomialQueue(){
		MakeEmpty();
	}
	void merge(BinomialQueue& rhs){
		if(this==&rhs)
			return;
		currentSize+=rhs.currentSize;
		if(currentSize>Capacity()){
			int oldValue=theTree.size();
			int newValue=std::max(theTree.size(),rhs.theTree.size())+1;
			theTree.resize(newValue);
			for(int i=oldValue;i<newValue;i++)
				theTree[i]=NULL;
		}
		BinomialNode* carry=NULL;//进位标志
		for(int i=0;i<theTree.size();i++){
			BinomialNode* t1=theTree[i];
			BinomialNode* t2=i<rhs.theTree.size()?rhs.theTree[i]:NULL;
			int whichCase=t1==NULL?0:1;
			whichCase+=t2==NULL?0:2;
			whichCase+=carry==NULL?0:4;
			switch(whichCase){
			case 0://allNULL
			case 1://rhs NULL
				break;
			case 2://this NULL
				theTree[i]=t2;
				rhs.theTree[i]=NULL;
				break;
			case 3://carry NULL
				carry=combineTrees(t1,t2);
				theTree[i]=rhs.theTree[i]=NULL;
				break;
			case 4://only carry
				theTree[i]=carry;
				carry=NULL;
				break;
			case 5://rhs NULL
				carry=combineTrees(t1,carry);
				theTree[i]=NULL;
				break;
			case 6://this NULL
				carry=combineTrees(t2,carry);
				rhs.theTree[i]=NULL;
				break;
			case 7://all
				theTree[i]=carry;
				carry=combineTrees(t1,t2);
				rhs.theTree[i]=NULL;
				break;
			}
		}
		rhs.currentSize=0;
	}
	void Insert(const T& x){
		merge(BinomialQueue(x));
	}
	bool isEmpty()const{
		return currentSize==0;
	}
	const T& findMin()const{
		if(isEmpty())
			throw;
		return theTree[findMinIndex()]->element;
	}
	void deleteMin(){
		if(isEmpty())
			return;
		int minIndex=findMinIndex();
		BinomialNode* oldValue=theTree[minIndex];
		theTree[minIndex]=NULL;
		BinomialNode* newValue=oldValue->leftChild;
		delete oldValue;
		currentSize-=pow(2.0,minIndex);
		BinomialQueue newQueue;
		newQueue.theTree.resize(minIndex);
		newQueue.currentSize=pow(2.0,minIndex)-1;
		for(int i=minIndex-1;i>=0;i--){
			newQueue.theTree[i]=newValue;
			newValue=newValue->nextSibling;
			newQueue.theTree[i]->nextSibling=NULL;
		}
		merge(newQueue);
	}
	void MakeEmpty(){
		for(int i=0;i<theTree.size();i++){
			MakeEmpty(theTree[i]);
		}
		currentSize=0;
	}
private:
	BinomialNode* combineTrees(BinomialNode* t1,BinomialNode* t2){
		if(t2->element<t1->element)
			return combineTrees(t2,t1);
		t2->nextSibling=t1->leftChild;
		t1->leftChild=t2;
		return t1;
	}
	int Capacity()const{
		return pow(2.0,long(theTree.size()))-1;
	}
	int findMinIndex()const{
		int minIndex=0;
		for(int i=0;i<theTree.size();i++)
			if(theTree[i]!=NULL){
				minIndex=i;
				break;
			}
		for(int i=minIndex+1;i<theTree.size();i++){
			if(theTree[i]!=NULL&&theTree[i]->element<theTree[minIndex]->element)
				minIndex=i;
		}
		return minIndex;
	}
	void MakeEmpty(BinomialNode*& t){
		if(t!=NULL){
			MakeEmpty(t->leftChild);
			MakeEmpty(t->nextSibling);
			delete t;
		}
		t=NULL;
	}
	BinomialNode* Clone(BinomialNode* t)const{
		if(t==NULL)
			return NULL;
		return new BinomialNode(t->element,Clone(t->leftChild),Clone(t->nextSibling));
	}
};