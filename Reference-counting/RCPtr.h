#pragma once
#include <cstdlib>

template<typename T>
class RCPtr{
public:
	RCPtr(T* realPtr=0);
	RCPtr(const RCPtr& rhs);
	~RCPtr();
	const RCPtr& operator=(const RCPtr& rhs);
	T* operator->()const;
	T& operator*()const;
private:
	T* pointee;
	void Init();
};
template<typename T>
RCPtr<T>::RCPtr(T* realPtr):pointee(realPtr){
	Init();
}
template<typename T>
RCPtr<T>::RCPtr(const RCPtr<T>& rhs):pointee(rhs.pointee){
	Init();
}
template<typename T>
const RCPtr<T>& RCPtr<T>::operator=(const RCPtr<T>& rhs){
	if(pointee!=rhs.pointee){
		if(pointee){
			pointee->removeReference();
		}
		pointee=rhs.pointee;
		Init();
	}
	return *this;
}
template<typename T>
RCPtr<T>::~RCPtr(){
	if(pointee)
		pointee->removeReference();
}
template<typename T>
void RCPtr<T>::Init(){
	if(pointee==NULL)
		return;
	if(pointee->isShareable()==false)
		pointee=new T(*pointee);
	pointee->addReference();
}

template<typename T>
T* RCPtr<T>::operator->()const{
	return pointee;
}

template<typename T>
T& RCPtr<T>::operator*()const{
	return *pointee;
}