#include <iostream>
#include <random>

template<typename T>
void swap(T& x1, T& x2){
	T temp;
	temp=x1;
	x1=x2;
	x2=temp;
}
//比较操作的次数
void max2(int A[],int lo ,int hi,int & x1,int & x2){
	if(lo+2==hi){
		x1=lo;
		x2=lo+1;
		if(A[x1]<A[x2])
			swap(x1,x2);
		return;
	}//T(2)=1
	if(lo+3==hi){
		x1=lo;
		x2=lo+1;
		if(A[x1]<A[x2])
			swap(x1,x2);
		if(A[x2]<A[hi-1])
			if(A[x1]<A[x2=hi-1])
				swap(x1,x2);
		return;
	}//T(3)<=3
	int mid=(lo+hi)/2;
	int x1l,x2l,x1r,x2r;
	max2(A,lo,mid,x1l,x2l);//T(n/2)
	max2(A,mid,hi,x1r,x2r);//T(n/2)
	if(A[x1l]>A[x1r]){
		x1=x1l;
		x2=(A[x1r]>A[x2l])?x1r:x2l;
	}
	else{
		x1=x1r;
		x2=(A[x1l]>A[x2r])?x1l:x2r;
	}//1+1=2

}
//T(n)=2*T(n/2)+2
int main(){
	int A[10],x1,x2;
	 std::default_random_engine generator;
	 std::uniform_int_distribution<int> distribution(0,1000);
	 for(int i=0;i<20;i++)
		 A[i]=distribution(generator);
	 for(int i=0;i<10;i++)
		 std::cout<<A[i]<<" ";
	 std::cout<<std::endl;
	 max2(A, 0, 11, x1, x2);
	 std::cout<<A[x1]<<"  "<<A[x2]<<std::endl;
}
