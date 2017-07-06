#pragma once 
#include "RCObject.h"
#include "RCPtr.h"
#include <cstring>
#include <iostream>

class String{
private:
	struct StringValue:public RCObject{
		StringValue(const char* realValue);
		StringValue(const StringValue& rhs);
		~StringValue();
		char *data;
	};
public:
	String(const char* value="");
	String(const String& rhs);
	const char& operator[](int index)const;
	char& operator[](int index);
	void print(){
		std::cout<<&value->data<<"\n";
	}
private:
	RCPtr<StringValue> value;
};
String::StringValue::StringValue(const char* realValue){
	data=new char[strlen(realValue)+1];
	strcpy(data,realValue);
}
String::StringValue::StringValue(const StringValue& rhs){
	data=new char[strlen(rhs.data)+1];
	strcpy(data,rhs.data);
}
String::StringValue::~StringValue(){
	delete [] data;
}
String::String(const char* value):value(new StringValue(value)){

}
String::String(const String& rhs):value(rhs.value){

}
const char& String::operator[](int index)const{
	return value->data[index];
}
char& String::operator[](int index){
	if(value->isShared()){
		value=new StringValue(value->data);
	}
	value->markUnshareable();
	return value->data[index];
}