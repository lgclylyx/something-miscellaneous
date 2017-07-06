#pragma once
#include <vector>

template<typename T>
class myQueue{
public:
	myQueue(int num):object(num),head(num-1),tail(0),theSize(num){
	}
	myQueue(const myQueue& rhs){
		object=rhs.object;
		head=rhs.head;
		tail=rhs.tail;
		theSize=rhs.theSize;
	}
	const myQueue& operator=(const myQueue& rhs){
		if(this==&rhs)
			return *this;
		object=rhs.object;
		head=rhs.head;
		tail=rhs.tail;
		theSize=rhs.theSize;
		return *this;
	}
	~myQueue(){
	}
	void Enqueue(const T& x){
		if((tail+1)%theSize>head)
			throw; 
		object[tail]=x;
		tail=++tail%theSize;
	}
	const T& Dequeue(){
		head=++head%theSize;
		if(head==tail)
			throw;
		return object[head];
	}
	bool IsEmpty()const{
		return (head+1)%theSize==tail?true:false;
	}
private:
	int head;
	int tail;
	int theSize;
	std::vector<T> object;
};