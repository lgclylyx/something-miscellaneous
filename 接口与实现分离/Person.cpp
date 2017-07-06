#include"Person.h"
CPerson::CPerson(const std::string& name,const CDate& birthday):m_pImpl(new CPersonImpl(name,birthday)){
}
void CPerson::print(void){
	m_pImpl->print();
}