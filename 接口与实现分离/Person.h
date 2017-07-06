#ifndef _person_h
#define _person_h
#include<string>
#include"date.h"
#include"PersonImpl.h"
#include<memory>
class CPerson{
public:
	explicit CPerson(const std::string& name,const CDate& birthday);
	void print(void);
private:
	std::tr1::shared_ptr<CPersonImpl> m_pImpl;
};
#endif