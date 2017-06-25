#ifndef KMP_H
#define KMP_H

#include <string>


using std::string;

int* buildNext(const string& P){
	int* N = new int[P.size()];
	int m = P.size();
	int j = 0;
	int t = N[0] = -1;//next���һ��Ϊ-1���ҵ�ǰ��ƥ���λ�õ�ƥ��ǰ�е��ƥ��ǰǰ׺�ͺ�׺�ĳ���Ϊt
	while(j < m-1){//ÿ�����Ѵ����������ƥ����Ӵ���ǰ׺�м���һλ�����λ�õ�next���ֵ�����t�ϼ���1
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
