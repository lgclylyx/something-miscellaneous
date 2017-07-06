#pragma once

#include <cstdlib>
#include <exception>

template<typename T>
class myListLazyDelete{
private:
	struct Node{
		bool flag;
		T data;
		Node* next;
		Node* prev;
		Node(const T& x=T(),Node* p=NULL,Node* n=NULL,bool f=false):data(x),prev(p),next(n),flag(f){}
	};
public:
	class const_iterator{
	public:
		const_iterator():current(NULL),theList(NULL){}
		const T& operator*(){
			return current->data;
		}
		const_iterator& operator++(){
			current=current->next;
			while(current->flag)
				current=current->next;
			return *this;
		}
		const_iterator operator++(int){
			const_iterator oldValue=*this;
			++(*this);
			return oldValue;
		}
		const_iterator& operator--(){
			current=current->prev;
			while(current->flag)
				current=current->prev;
			return *this;
		}
		const_iterator operator--(int){
			const_iterator oldValue=*this;
			--(*this);
			return oldValue;
		}
		bool operator==(const const_iterator& rhs)const{
			return current==rhs.current;
		}
		bool operator!=(const const_iterator& rhs)const{
			return !(*this==rhs);
		}
	protected:
		Node* current;
		const myListLazyDelete<T>* theList;
		void assertIsValid()const{
			if(theList==NULL||current==NULL||current==theList->head)
				throw;
		}
		const_iterator(const myListLazyDelete<T>& rhs,Node* p):theList(&rhs),current(p){}
		friend class myListLazyDelete<T>;
	};
	class iterator:public const_iterator{
	public:
		iterator(){}
		T& operator*(){
			return current->data;
		}
		iterator& operator++(){
			current=current->next;
			while(current->flag)
				current=current->next;
			return *this;
		}
		iterator operator++(int){
			iterator oldValue=*this;
			++(*this);
			return oldValue;
		}
		iterator& operator--(){
			current=current->prev;
			while(current->flag)
				current=current->prev;
			return *this;
		}
		iterator operator--(int){
			iterator oldValue=*this;
			--(*this);
			return oldValue;
		}
	private:
		iterator(const myListLazyDelete<T>& rhs,Node* p):const_iterator(rhs,p){}
		friend class myListLazyDelete<T>;
	};
public:
	myListLazyDelete(){
		Init();
	}
	myListLazyDelete(const myListLazyDelete& rhs){
		Init();
		theSize=rhs.theSize;
		for(const_iterator itr=rhs.Begin();itr!=rhs.End();++itr)
			Push_Back(*itr);
	}
	const myListLazyDelete& operator=(const myListLazyDelete& rhs){
		if(this==&rhs)
			return *this;
		clear();
		theSize=rhs.theSize;
		for(const_iterator itr=rhs.Begin();itr!=rhs.End();++itr)
			Push_Back(*itr);
		return *this;
	}
	~myListLazyDelete(){
		clear();
		delete head;
		delete tail;
	}
	iterator Begin(){
		iterator itr(*this,head);
		return ++itr;
	}
	const_iterator Begin()const{
		const_iterator itr(*this,head);
		return ++itr;
	}
	iterator End(){
		return iterator(*this,tail);
	}
	const_iterator End()const{
		return const_iterator(*this,tail);
	}
	int Size()const{
		return theSize;
	}
	bool IsEmpty()const{
		return theSize==0;
	}
	T& Front(){
		return *Begin();
	}
	const T& Front()const{
		return *Begin();
	}
	T& Back(){
		return *(--End());
	}
	const T& Back()const{
		return *(--End());
	}
	void Push_Front(const T& x){
		Insert(begin(),x);
	}
	void Push_Back(const T& x){
		Insert(End(),x);
	}
	iterator Insert(iterator itr,const T& x){
		itr.assertIsValid();
		if(itr.theList!=this)
			throw;
		Node* p=itr.current;
		theSize++;
		return iterator(*this,p->prev=p->prev->next=new Node(x,p->prev,p));
	}
	void Pop_Front(){
		Erase(Begin());
	}
	void Pop_Back(){
		Erase(--End());
	}
	iterator Erase(iterator itr){
		itr.assertIsValid();
		if(itr.theList!=this||itr==End())
			throw;
		++theSize_Delete;
		--theSize;
		itr.current->flag=true;
		itr.current=itr.current->next;
		if(theSize_Delete>=theSize){
			DeepDelete();
		}
		return itr;
	}
	void DeepDelete(){
		Node* p=head->next;
		while(p!=tail){
			if(p->flag){
				p->next->prev=p->prev;
				p->prev->next=p->next;
			}
			Node* s=p;
			p=p->next;
			if(s->flag)
				delete s;
		}
		theSize_Delete=0;
	}
	iterator Erase(iterator start,iterator end){
		for(iterator itr=start;itr!=end;)
			itr=Erase(itr);
		return end;
	}
	void clear(){
		Erase(Begin(),End());
		theSize=0;
		theSize_Delete=0;
	}
private:
	Node* head;
	Node* tail;
	int theSize;
	int theSize_Delete;
	void Init(){
		theSize=0;
		theSize_Delete=0;
		head=new Node;
		tail=new Node;
		head->next=tail;
		tail->prev=head;
	}
};