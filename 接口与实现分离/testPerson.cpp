#include"date.h"
#include"Person.h"
int main(){
	CDate birthday(2,6,2016);
	CPerson person("liu",birthday);
	person.print();
	return 0;
}