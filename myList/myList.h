#pragma once
#include <cstdlib>

template<typename T>
class myList{
private:
	struct Node{
		T data;
		Node* prev;
		Node* next;
		Node(const T& x=T(),Node* p=NULL,Node* n=NULL):data(x),prev(p),next(n){

		}
	};
public:
	class const_iterator{
	public:
		const_iterator():current(NULL){

		}
		const T& operator*()const{
			return current->data;
		}
		const_iterator& operator++(){
			current=current->next;
			return *this;
		}
		const const_iterator operator++(int){
			const_iterator oldValue=*this;
			++(*this);
			return oldValue;
		}
		const_iterator& operator--(){
			current=current->prev;
			return *this;
		}
		const const_iterator operator--(int){
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
		const_iterator(Node* p):current(p){

		}
		friend class myList<T>;
	};
	class iterator:public const_iterator{
	public:
		iterator(){

		}
		const T& operator*()const{
			return current->data;
		}
		T& operator*(){
			return current->data;
		}
		iterator& operator++(){
			current=current->next;
			return *this;
		}
		const iterator operator++(int){
			iterator oldValue=*this;
			++(*this);
			return oldValue;
		}
		iterator& operator--(){
			current=current->prev;
			return *this;
		}
		const iterator operator--(int){
			iterator oldValue=*this;
			--(*this);
			return oldValue;
		}
	protected:
		iterator(Node* p):const_iterator(p){

		}
		friend class myList<T>;
	};
public:
	myList();
	myList(const myList& rhs);
	const myList& operator=(const myList& rhs);
	~myList();
	int Size()const;
	bool IsEmpty()const;
	iterator begin();
	const_iterator begin()const;
	iterator end();
	const_iterator end()const;
	T& front();
	const T& front()const; 
	T& back();
	const T& back()const;
	void push_front(const T& x);
	void push_back(const T& x);
	iterator insert(const T& x,iterator itr);
	void pop_front();
	void pop_back();
	iterator erase(iterator itr);
	iterator erase(iterator start,iterator end);
	void clear();
private:
	int theSize;
	Node* head;
	Node* tail;

};

template<typename T>
myList<T>::myList():theSize(0){
	head=new Node;
	tail=new Node;
	head->next=tail;
	tail->prev=head;
}

template<typename T>
myList<T>::myList(const myList<T>& rhs){
	head=new Node;
	tail=new Node;
	head->next=tail;
	tail->prev=head;
	for(const_iterator itr=begin();itr!=end();++itr)
		push_back(*itr);
}

template<typename T>
const myList<T>& myList<T>::operator=(const myList<T>& rhs){
	if(this==&rhs)
		return *this;
	clear();
	for(const_iterator itr=begin();itr!=end();++itr)
		push_back(*itr);
	return *this;
}

template<typename T>
myList<T>::~myList(){
	clear();
	delete head;
	delete tail;
}

template<typename T>
int myList<T>::Size()const{
	return theSize;
}

template<typename T>
bool myList<T>::IsEmpty()const{
	return theSize==0;
}

template<typename T>
typename myList<T>::iterator myList<T>::begin(){
	return iterator(head->next);
}

template<typename T>
typename myList<T>::const_iterator myList<T>::begin()const{
	return const_iterator(head->next);
}

template<typename T>
typename myList<T>::iterator myList<T>::end(){
	return iterator(tail);
}

template<typename T>
typename myList<T>::const_iterator myList<T>::end()const{
	return const_iterator(tail);
}

template<typename T>
T& myList<T>::front(){
	return *begin();
}

template<typename T>
const T& myList<T>::front()const{
	return *begin();
}

template<typename T>
T& myList<T>::back(){
	return *--end();
}

template<typename T>
const T& myList<T>::back()const{
	return *--end();
}

template<typename T>
void myList<T>::push_back(const T& x){
	insert(x,end());
}

template<typename T>
void myList<T>::push_front(const T& x){
	insert(x,begin()):
}

template<typename T>
typename myList<T>::iterator myList<T>::insert(const T& x,iterator itr){
	theSize++;
	return iterator(itr.current->prev=itr.current->prev->next=new Node(x,itr.current->prev,itr.current));
}

template<typename T>
void myList<T>::pop_front(){
	erase(begin());
}

template<typename T>
void myList<T>::pop_back(){
	erase(--end());
}

template<typename T>
typename myList<T>::iterator myList<T>::erase(iterator itr){
	Node* p=itr.current;
	itr.current=itr.current->next;
	p->next->prev=p->prev;
	p->prev->next=p->next;
	delete p;
	theSize--;
	return itr;
}

template<typename T>
typename myList<T>::iterator myList<T>::erase(iterator start,iterator end){
	for(iterator itr=start;itr!=end;)
		itr=erase(itr);
	return end;
}

template<typename T>
void myList<T>::clear(){
	erase(begin(),end());
}


