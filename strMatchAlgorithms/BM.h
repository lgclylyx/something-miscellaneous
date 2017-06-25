#ifndef BM_H
#define BM_H

#include <string>

using std::string;

int * buildBC(const string& P){//��¼ģʽ���У���ͬԪ�������ұߵ��Ǹ�Ԫ�ص�Rank
	int m = P.size();
	int* BC = new int[256];
	for(int i = 0;i <256;i++)
		BC[i] = -1;
	for(int i = 0;i < m;i++){
		BC[int(P[i])] = i;
	}
	return BC;
}

void suffixes(const char *P, int m, int *suff) {//����ģʽ����λ��i~[0,m),����P[0,i]�еĺ�׺������P�еĺ�׺���ƥ�䳤��
   int nearestmatched_i, outofnearestmatched, current_P;
   suff[m - 1] = m;//���һλ�϶�ȫ��ƥ��
   outofnearestmatched = m - 1;
   for (current_P = m - 2; current_P >= 0; --current_P) {
      if (current_P > outofnearestmatched && suff[current_P + m - 1 - nearestmatched_i] < current_P - outofnearestmatched)//����ƥ��ɹ�������£�ƥ��ɹ��ĳ���Ϊ��g,i]��iΪĳ�θ�ƥ��ɹ���û�и��µ�iֵ,�����º��iֵû�е���g���������ϴ�ƥ��ķ�Χ��ʱ���������P�ĺ�׺�����뵱ǰiֵ��ͬ��Ԫ�أ����һ����Թ�ƥ�䳤�ȣ�����������£�
         suff[current_P] = suff[current_P + m - 1 - nearestmatched_i];//���suff[i + m - 1 - f] < i - g�����ϴε�ƥ�䳤��С�ڱ���ʣ���ƥ�䳤�ȣ������ڵ�i��g�ķ�Χ(g,i]����ƥ�䳤��Ӧ�����ϴ�ʱ�ĳ���һ�¡�����ʹӾʹ�g��ʼ�ȶԿ��Ƿ������ӵĳ��ȡ�
      else {
         if (current_P < outofnearestmatched)
            outofnearestmatched = current_P;
         nearestmatched_i = current_P;
         while (outofnearestmatched >= 0 && P[outofnearestmatched] == P[outofnearestmatched + m - 1 - nearestmatched_i])//��i��ʼ������������λ�Ƚ��Ƿ�ƥ��
            --outofnearestmatched;
         suff[current_P] = nearestmatched_i - outofnearestmatched;
      }
   }
}

int* buildGS(const string& P){//����GS����¼��P[i]������ʧ��ʱ���ƶ�����GS[i]
	int m = P.size();
	int* suff = new int[m];
	int* GS = new int[m];
	int j = 0;
	suffixes(P.c_str(),m,suff);
	for(int i=0;i<m;i++)//��ʼ��Ϊ������ƥ������
		GS[i] = m;
	for(int i=m-1;i>=0;i--)//��suff[i]==i+1���������P[0,i]ƥ����������P[0,m-i-1)�г��ֲ�ƥ��ʱ���ƶ��ľ��붼��m-i-1����i��m-1��ʼ����֤��m-i-1��ֵ��i��С�����󣬱�֤��ѡ���������������ƶ�������С��ƥ����������i�������Ǳ�֤ÿһ��GS���󱻸���һ��
		if(i+1 == suff[i])
			while(j < m-1-i)
				GS[j++] = m-i-1;
	for(int i=0;i<m-1;i++)//��������suff[i]==i+1ʱ��P[m-ss[i]-1]������ʧ��ʱ�����ƶ���i��,���ƶ�m-1-i�����Ҵ�ʱ�ĵ�m-1-i��ֵһ����gs[m-ss[i]-1]��ֵС����Ϊ��ʱGS��λ�õ�ֵΪm��������һ��ѭ���е�(��ʱi<��ʱss[i])ʱ��m-i-1����Ϊss[i]<=i+1;��Ȼss[i]С�ڵ���i,����m-ss[i](��ʱ��ss[i]��Ϊ��ʱ��i)-1>=m-i-1
		GS[m-1-suff[i]] = m-i-1;
	delete [] suff;
	return GS;
}

int matchWithBM(const string& T,const string& P){
	int* BC = buildBC(P);
	int* GS = buildGS(P);
	int i = 0 , j = 0;
	int n = T.size() , m = P.size() ;
	while(n >= i + m){
		j = m - 1;
		while(P[j] == T[i+j])
			if(0 > --j) break;
		if(0 > j)
			break;
		else
			i += std::max(GS[j], j - BC[int(T[i+j])]);
	}
	delete [] BC;
	delete [] GS;
	return i;
}
#endif
