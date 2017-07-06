#pragma once
#include <cstdlib>

template<typename T>
class myQueueList{
private:
	struct Node{
		Node* next;
		T data;
		Node(const T& t=T(),Node* n=NULL):data(t),next(n){}
	};
	struct LinkQueue{
		Node* head;
		Node* tail;
		LinkQueue():head(NULL),tail(NULL){}
	};
public:
	myQueueList(){
		object=new LinkQueue;
	}
	myQueueList(const myQueueList& rhs){
		object=new LinkQueue;
		Node* p=rhs.object->head;
		while(p!=NULL){
			Enqueue(p->data);
			p=p->next;
		}
	}
	const myQueueList& operator=(const myQueueList& rhs){
		if(this==&rhs)
			return *this;
		clear();
		Node* p=rhs.object->head;
		while(p!=NULL){
			Enqueue(p->data);
			p=p->next;
		}
		return *this;
	}
	~myQueueList(){
		clear();
		delete object;
	}
	void Enqueue(const T& x){
		Node* p=new Node(x);
		if(IsEmpty()){
			object->head=p;
			object->tail=p;
		}else{
			object->tail->next=p;
			object->tail=p;
		}
	}
	T Dequeue(){
		if(IsEmpty())
			throw;
		Node* s=object->head;
		T t=s->data;
		object->head=object->head->next;
		if(object->head==NULL)
			object->tail=NULL;
		delete s;
		return t;
	}
	bool IsEmpty()const{
		return object->head==NULL&&object->tail==NULL;
	}
	void clear(){
		while(!IsEmpty()){
			Node* s=object->head;
			object->head=object->head->next;
			if(object->head==NULL)
				object->tail=NULL;
			delete s;
		}
	}
private:
	LinkQueue* object;
};