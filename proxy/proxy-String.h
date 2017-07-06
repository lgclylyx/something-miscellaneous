#ifndef _proxy_String 
#define _proxy_String

#include <cstring>

class RCObject{
public:
	void addReference();
	void removeReference();
	void markUnshareable();
	bool isShared()const;
	bool isShareable()const;
protected:
	RCObject();
	RCObject(const RCObject& rhs);
	const RCObject& operator=(const RCObject& rhs);
	virtual ~RCObject();
private:
	int rfCount;
	bool shareable;
};

RCObject::RCObject():rfCount(0),shareable(true){

}

RCObject::RCObject(const RCObject& rhs):rfCount(0),shareable(true){

}

const RCObject& RCObject::operator=(const RCObject& rhs){
	return *this;
}

RCObject::~RCObject(){

}

void RCObject::markUnshareable(){
	shareable=false;
}

bool RCObject::isShareable()const{
	return shareable;
}

bool RCObject::isShared()const{
	return rfCount>1;
}

void RCObject::addReference(){
	++rfCount;
}

void RCObject::removeReference(){
	if(--rfCount==0)
		delete this;
}

template<typename T>
class RCPtr{
public:
	RCPtr(T* realValue=0);
	RCPtr(const RCPtr& rhs);
	const RCPtr& operator=(const RCPtr& rhs);
	~RCPtr();
	T* operator->()const;
	T& operator*()const;
private:
	T* pointee;
	void Init();
};

template<typename T>
RCPtr<T>::RCPtr(T* realValue):pointee(realValue){
	Init();
}

template<typename T>
RCPtr<T>::RCPtr(const RCPtr<T>& rhs):pointee(rhs.pointee){
	Init();
}

template<typename T>
const RCPtr<T>& RCPtr<T>::operator=(const RCPtr<T>& rhs){
	if(pointee!=rhs.pointee){
		if(pointee)
			pointee->removeReference();
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
T* RCPtr<T>::operator->()const{
	return pointee;
}

template<typename T>
T& RCPtr<T>::operator*()const{
	return *pointee;
}

template<typename T>
void RCPtr<T>::Init(){
	if(pointee==NULL)
		return;
	if(pointee->isShareable()==false)
		pointee=new T(*pointee);
	pointee->addReference();
}

class String{
public:
	class proxy{
	public:
		proxy(String& s,int index);
		proxy& operator=(const proxy& rhs);
		proxy& operator=(char c);
		operator char()const;
	private:
		String& theString;
		int charIndex;
	};
private:
	struct StringValue:public RCObject{
		StringValue(const char * initValue);
		StringValue(const StringValue& rhs);
		void Init(const char * initValue);
		~StringValue();
		char * data;
	};
public:
	String(const char* value="");
	const proxy operator[](int index)const;
	proxy operator[](int index);
private:
	RCPtr<StringValue> value;
	friend class proxy;
};

String::StringValue::StringValue(const char* initValue){
	Init(initValue);
}

String::StringValue::StringValue(const String::StringValue& rhs){
	Init(rhs.data);
}

void String::StringValue::Init(const char * initValue){
	data=new char[strlen(initValue)+1];
	strcpy(data,initValue);
}

String::StringValue::~StringValue(){
	delete [] data;
}

String::proxy::proxy(String& s,int index):theString(s),charIndex(index){

}

String::proxy& String::proxy::operator=(const proxy& rhs){
	if(theString.value->isShared())
		theString.value=new StringValue(theString.value->data);
	theString.value->data[charIndex]=rhs.theString.value->data[rhs.charIndex];
	return *this;
}

String::proxy::operator char()const{
	return theString.value->data[charIndex];
}

String::proxy& String::proxy::operator=(char c){
	if(theString.value->isShared())
		theString.value=new StringValue(theString.value->data);
	theString.value->data[charIndex]=c;
	return *this;
}

String::String(const char* value):value(new StringValue(value)){

}

const String::proxy String::operator[](int index)const{
	return proxy(const_cast<String&>(*this),index);
}

String::proxy String::operator[](int index){
	return proxy(*this,index);
}

#endif 