//accomplished by complete binary tree
#pragma once
#include <vector>
#include <iostream>
#include <climits>

template<typename T>
class BinaryHeap{
public:
	BinaryHeap(int theCapacity=100):theSize(0){
		theheap.resize(theCapacity);
	}
	BinaryHeap(const std::vector<T>& rhs):theSize(rhs.size()){
		theheap.resize(rhs.capacity());
		for(int i=0;i<rhs.size();i++){
			theheap.at(i+1)=rhs.at(i);
		}
		buildHeap();
	}
	void Insert(const T& x){
		if(theSize==theheap.capacity()-1)
			theheap.resize(theheap.capacity()*2);
		int hole=++theSize;
		while(true){//上滤
			if(hole>1&&x<theheap.at(hole/2))
				theheap.at(hole)=theheap.at(hole/2);
			else
				break;
			hole=hole/2;
		}
		theheap.at(hole)=x;
	}
	void deleteMin(){
		if(IsEmpty())
			return;
		theheap.at(1)=theheap.at(theSize--);
		percolateDown(1);
	}
	bool IsEmpty()const{
		return theSize==0;
	}
	void print()const{
		for(int i=1;i<=theSize;i++)
			std::cout<<theheap.at(i)<<"	";
		std::cout<<std::endl;
	}
	void DecreaseKey(int p,const T& delta){
		T temp=theheap.at(p)-delta;
		for(;p>1;){
			if(temp<theheap.at(p/2)){
				theheap.at(p)=theheap.at(p/2);
				p=p/2;
			}else{
				break;
			}
		}
		theheap.at(p)=temp;
	}
	void IncreaseKey(int p,const T& delta){
		T temp=theheap.at(p)+delta;
		int child=2*p;
		for(;child<=theSize;){
			if(child!=theSize&&theheap.at(child+1)<theheap.at(child))
				++child;
			if(theheap.at(child)<temp)
				theheap.at(p)=theheap.at(child);
			else
				break;
			p=child;
			child=2*p;
		}
		theheap.at(p)=temp;
	}
	void remove(int p){
		DecreaseKey(p,INT_MAX);
		deleteMin();
	}
private:
	void percolateDown(int hole){
		int temp=theheap.at(hole);
		int child=2*hole;
		while(child<=theSize){
			if(child!=theSize//只有一个孩子的情况
				&&theheap.at(child+1)<theheap.at(child))
				++child;
			if(theheap.at(child)<temp)
				theheap.at(hole)=theheap.at(child);
			else
				break;
			hole=child;
			child=2*hole;
		}
		theheap.at(hole)=temp;
	}
	void buildHeap(){
		for(int i=theSize/2;i>=1;i--)
			percolateDown(i);
	}
	std::vector<T> theheap;
	int theSize;
};