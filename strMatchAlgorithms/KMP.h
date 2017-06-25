#ifndef KMP_H
#define KMP_H

#include <string>


using std::string;

int* buildNext(const string& P){
	int* N = new int[P.size()];
	int m = P.size();
	int j = 0;
	int t = N[0] = -1;//next表第一项为-1，且当前不匹配的位置的匹配前中的最长匹配前前缀和后缀的长度为t
	while(j < m-1){//每次在已处理过的用于匹配的子串的前缀中加上一位，则该位置的next表的值最多在t上加上1
		if(0 > t || P[j] == P[t]){
			j++;
			t++;
			N[j] = P[j] == P[t] ? t: N[t];
		}else
			t = N[t];
	}
	return N;
}
int matchWithKMP(const string& T,const string& P){
	int* Next = buildNext(P);
	int i = 0 , j = 0;
	int m = P.size() , n = T.size();
	while(j < m && i < n){
		if(0 > j || T[i] == P[j])
			++i , ++j;
		else
			j = Next[j];
	}
	delete [] Next;
	return i-j;
}

#endif
