#include"date.h"
#include<iostream>
using std::cout;
CDate::CDate(int mon,int day,int year):mon(mon),day(day),year(year){
}
CDate::~CDate(){
}
void CDate::Print(void){
	cout<<mon<<" "<<day<<" "<<year;
}