#pragma once

template<typename T>
class Vector{
public:
	Vector(int initSize=0);
	Vector(const Vector<T>& rhs);
	const Vector<T>& operator=(const Vector<T>& rhs);
	~Vector();
	bool IsEmpty()const;
	int Size()const;
	int Capacity()const;
	const T& operator[](int index)const;
	T& operator[](int index);
	void Reserve(int newCapacity);
	void Resize(int newSize);
	void push_back(const T& x);
	void pop_back();
	const T& back()const;
	typedef T* iterator;
	typedef const T* const_iterator;
	iterator begin();
	const_iterator begin()const;
	iterator end();
	const_iterator end()const;
	enum{SPARE_CAPACITY=16};
private:
	int theSize;
	int theCapacity;
	T* object;
};

template<typename T>
Vector<T>::Vector(int initSize):theSize(initSize),theCapacity(SPARE_CAPACITY+initSize){
	object=new T[theCapacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& rhs){
	theSize=rhs.theSize;
	theCapacity=rhs.theCapacity;
	object=new T[theCapacity];
	for(int i=0;i<theSize;i++)
		object[i]=rhs.object[i];
}

template<typename T>
const Vector<T>& Vector<T>::operator=(const Vector<T>& rhs){
	if(this!=&rhs){
		delete [] object;
		theSize=rhs.theSize;
		theCapacity=rhs.theCapacity;
		object=new T[theCapacity];
		for(int i=0;i<theSize;i++)
			object[i]=rhs.object[i];
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector(){
	delete [] object;
}

template<typename T>
bool Vector<T>::IsEmpty()const{
	return theSize>0?false:true;
}

template<typename T>
int Vector<T>::Size()const{
	return theSize;
}

template<typename T>
int Vector<T>::Capacity()const{
	return theCapacity;
}

template<typename T>
const T& Vector<T>::operator[](int index)const{
	return object[index];
}

template<typename T>
T& Vector<T>::operator[](int index){
	return object[index];
}

template<typename T>
void Vector<T>::Reserve(int newCapacity){
	if(newCapacity<theSize)
		return;
	T* oldValue=object;
	object=new T[newCapacity];
	for(int i=0;i<theSize;i++)
		object[i]=oldValue[i];
	theCapacity=newCapacity;
	delete [] oldValue;
}

template<typename T>
void Vector<T>::Resize(int newSize){
	if(newSize>theCapacity)
		Reserve(newSize*2+1);
	theSize=newSize;
}

template<typename T>
void Vector<T>::push_back(const T& x){
	if(theSize==theCapacity)
		Reserve(theCapacity*2+1);
	object[theSize++]=x;
}

template<typename T>
void Vector<T>::pop_back(){
	theSize--;
}

template<typename T>
const T& Vector<T>::back()const{
	return object[theSize-1];
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin(){
	return object;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin()const{
	return object;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end(){
	return &object[theSize];
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end()const{
	return &object[theSize];
}

