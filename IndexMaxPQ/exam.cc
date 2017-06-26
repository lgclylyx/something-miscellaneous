#include <iostream>
#include "IndexMaxPQ.cc"
/*
 * 用indexmaxpq实现多路归并
 */
int main(){
//	IndexMaxPQ<int> a(11);
//	int b[10] ={1,5,3,6,2,4,9,8,7,0};
//	for(int i =0;i<10;i++){
//		a.insert(i, b[i]);
//	}
//	for(int i = 0;i<10;i++){
//		std::cout<<a.max();
//		a.delMax();
//	}
	IndexMaxPQ<char> a(4);
	char x1[] = "ABCFGIIZ";
	char x2[] = "BDHPQQ";
	char x3[] = "ABEFJN";
	vector<char> m1;
	vector<char> m2;
	vector<char> m3;
	for(int i=0;i<sizeof(x1)-1;i++)
		m1.push_back(x1[i]);
	for(int i=0;i<sizeof(x2)-1;i++)
		m2.push_back(x2[i]);
	for(int i=0;i<sizeof(x3)-1;i++)
		m3.push_back(x3[i]);
	vector<vector<char> > m;
	m.push_back(m1);
	m.push_back(m2);
	m.push_back(m3);
	for(int i=0;i<m.size();i++)
		for(int j=0;j<m[i].size();j++){
			std::cout<<m[i][j]<<" ";
		}
	std::cout<<"\n";
	for(int i =0;i<3;i++)
		if(!m[i].empty()){
			a.insert(i+1, m[i].back());
			m[i].pop_back();
		}
	while(!a.isEmpty()){
		std::cout<< a.max()<<" ";
		int i = a.delMax();
		if(!m[i-1].empty()){
			a.insert(i, m[i-1].back());
			m[i-1].pop_back();
		}
	}
}
