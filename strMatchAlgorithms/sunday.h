#ifndef SUNDAY_H
#define SUNDAY_H

#include <string>

using std::string;

int* buildTable(const string& P){
	int m = P.size();
	int* tab = new int[256];
	for(int i=0;i<256;i++)
		tab[i] = m;
	for(int i=0;i<m;i++)
		tab[int(P[i])] = m-i;
	return tab;
}

int matchWithSunday(const string& T,const string& P){
	int m = P.size();
	int n = T.size();
	int* tab = buildTable(P);
	int i = 0,j = m-1;
	for(;j>=0&&i<=(n-m);){//从后往前匹配
		if(P[j]==T[i+j])
			j--;
		else{
			if(i+m<n)
				i+=tab[int(T[i+m])];//T[i+m]:当出现不匹配时，则T[i+m]则必定参加下一次匹配，移动到子串中最右边与T[i+m]相同处，或者直接跳过该位
			else
				break;
			j=m-1;
		}
	}
	return i;
}
#endif
