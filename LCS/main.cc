#include <iostream>

using namespace std;
//�ݹ�ⷨ��ָ�����Ӷȣ��ܶ�������ظ�����
int LCS(const char* A,int m,const char* B,int n){
	int max=0;
	if(m<=0||n<=0)
		return max;//ƽ������
	if(A[m-1]==B[n-1]){
		max=1+LCS(A,m-1,B,n-1);//������֮
	}else{
		int maxt1=0,maxt2=0;
		maxt1=LCS(A,m-1,B,n);
		maxt2=LCS(A,m,B,n-1);
		max=(maxt1>maxt2)?maxt1:maxt2;
	}//�ֶ���֮
	return max;
}
//�ö�̬�滮����ݹ飬���Ч��
int LCS_iterator(const char* A,int m,const char* B,int n){
	int ** table=new int*[n+1];
	for(int i=0;i<n+1;i++)
		table[i]=new int[m+1];//����һ��m*n�ı�

	for(int i=0;i<m+1;i++)
		table[0][i]=0;

	for(int i=0;i<n+1;i++)
		table[i][0]=0;//��ʼ����

	for(int i=1;i<n+1;i++)
		for(int j=1;j<m+1;j++){
			if(B[i-1]==A[j-1])
				table[i][j]=table[i-1][j-1]+1;
			else
				table[i][j]=(table[i-1][j]>table[i][j-1])?table[i-1][j]:table[i][j-1];
		}//����ȫ��
	int re=table[n][m];
	for(int i=0;i<n+1;i++){
		for(int j=0;j<m+1;j++)
			cout<<table[i][j]<<" ";
		cout<<endl;
	}
	for(int i=0;i<n+1;i++)
		delete[] table[i];
	delete[] table;
	return re;
}//O(m*n)

int main(){
	char A[]="didactical",B[]="advantage";
	cout<<LCS(A,sizeof(A)-1,B,sizeof(B)-1)<<endl;
	cout<<LCS_iterator(A,sizeof(A)-1,B,sizeof(B)-1)<<endl;
}
