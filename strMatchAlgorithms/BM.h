#ifndef BM_H
#define BM_H

#include <string>

using std::string;

int * buildBC(const string& P){//记录模式串中，相同元素中最右边的那个元素的Rank
	int m = P.size();
	int* BC = new int[256];
	for(int i = 0;i <256;i++)
		BC[i] = -1;
	for(int i = 0;i < m;i++){
		BC[int(P[i])] = i;
	}
	return BC;
}

void suffixes(const char *P, int m, int *suff) {//计算模式串中位置i~[0,m),其中P[0,i]中的后缀与整个P中的后缀的最长匹配长度
   int nearestmatched_i, outofnearestmatched, current_P;
   suff[m - 1] = m;//最后一位肯定全部匹配
   outofnearestmatched = m - 1;
   for (current_P = m - 2; current_P >= 0; --current_P) {
      if (current_P > outofnearestmatched && suff[current_P + m - 1 - nearestmatched_i] < current_P - outofnearestmatched)//在有匹配成功的情况下，匹配成功的长度为（g,i]，i为某次刚匹配成功还没有更新的i值,当更新后的i值没有到达g，即还在上次匹配的范围内时，则表明在P的后缀中有与当前i值相同的元素，而且还测试过匹配长度，在这种情况下，
         suff[current_P] = suff[current_P + m - 1 - nearestmatched_i];//如果suff[i + m - 1 - f] < i - g，即上次的匹配长度小于本次剩余的匹配长度，即现在的i到g的范围(g,i]，则匹配长度应该与上次时的长度一致。否则就从就从g开始比对看是否有增加的长度。
      else {
         if (current_P < outofnearestmatched)
            outofnearestmatched = current_P;
         nearestmatched_i = current_P;
         while (outofnearestmatched >= 0 && P[outofnearestmatched] == P[outofnearestmatched + m - 1 - nearestmatched_i])//从i开始，自右向左，逐位比较是否匹配
            --outofnearestmatched;
         suff[current_P] = nearestmatched_i - outofnearestmatched;
      }
   }
}

int* buildGS(const string& P){//返回GS表，记录在P[i]处发生失配时的移动距离GS[i]
	int m = P.size();
	int* suff = new int[m];
	int* GS = new int[m];
	int j = 0;
	suffixes(P.c_str(),m,suff);
	for(int i=0;i<m;i++)//初始化为不存在匹配的情况
		GS[i] = m;
	for(int i=m-1;i>=0;i--)//当suff[i]==i+1的情况，即P[0,i]匹配的情况，当P[0,m-i-1)中出现不匹配时，移动的距离都是m-i-1，而i从m-1开始，保证了m-i-1的值随i减小逐渐增大，保证了选择满足条件而且移动距离最小的匹配条件。而i的作用是保证每一个GS表象被更新一次
		if(i+1 == suff[i])
			while(j < m-1-i)
				GS[j++] = m-i-1;
	for(int i=0;i<m-1;i++)//当不满足suff[i]==i+1时，P[m-ss[i]-1]处发生失配时，可移动到i处,即移动m-1-i，而且此时的的m-1-i的值一定比gs[m-ss[i]-1]的值小，因为此时GS该位置的值为m或者在上一个循环中当(当时i<此时ss[i])时的m-i-1，因为ss[i]<=i+1;必然ss[i]小于等于i,所以m-ss[i](此时的ss[i]即为当时的i)-1>=m-i-1
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
