#include"PersonImpl.h"
#include<iostream>
#include<string>
CPersonImpl::CPersonImpl(const std::string& name,const CDate& birthday):name(name),birthday(birthday){
} 
void CPersonImpl::print(void){
	std::cout<<name<<" ";
	birthday.Print();
}