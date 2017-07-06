#ifndef _PersonImpl_h
#define _PersonImpl_h
#include<string>
#include"date.h"
class CPersonImpl{
public:
	CPersonImpl(const std::string& name,const CDate& birthday);
	void print(void);
private:
	std::string name;
	CDate birthday;
};
#endif