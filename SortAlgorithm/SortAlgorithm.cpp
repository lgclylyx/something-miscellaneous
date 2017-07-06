#include <iostream>
//#include <vector>
#include <random>
#include <ctime>
//#include <algorithm>
#include "SortAlgorithm.h"

//void InsertSort(std::vector<int>&);
//void ShellSort(std::vector<int>&);
//void HeapSort(std::vector<int>&);
//void mergeSort(std::vector<int>&);
//void mergeSort(std::vector<int>&,std::vector<int>&,int,int);
//void merge(std::vector<int>&,std::vector<int>&,int,int,int);
//void QuickSort(std::vector<int>&);
//void QuickSort(std::vector<int>&,int,int);
//int median3(std::vector<int>&,int,int);
int main(){
	SortAlgorithm SA;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,10000000);
	std::vector<int> oriData;
	for(int i=0;i<5000000;i++){
		oriData.push_back(distribution(generator));
	}
	//for(int i=0;i<oriData.size();i++){
	//	std::cout<<oriData[i]<<"	";
	//}
	//std::cout<<std::endl;
	clock_t begin=clock();
	//InsertSort(oriData);
	//ShellSort(oriData);
	//HeapSort(oriData);
	//mergeSort(oriData);
	SA.QuickSort(oriData);
	clock_t end=clock();
	//for(int i=0;i<oriData.size();i++){
	//std::cout<<oriData[i]<<"	";
	//}
	//std::cout<<std::endl;
	std::cout<<(end-begin)/CLOCKS_PER_SEC<<std::endl;
	system("pause");
	return 0;
}

//void InsertSort(std::vector<int>& oriData){
//	for(int p=1;p<oriData.size();p++){
//		int temp=oriData[p];
//		int j=p;
//		for(;j>0&&temp<oriData[j-1];j--){
//			oriData[j]=oriData[j-1];
//		}
//		oriData[j]=temp;
//	}
//}

//void ShellSort(std::vector<int>& oriData){
//	for(int gap=oriData.size();gap>0;gap/=2){
//		for(int j=gap;j<oriData.size();j++){
//			int temp=oriData[j];
//			int i=j;
//			for(;i>=gap&&temp<oriData[i-gap];i-=gap){
//				oriData[i]=oriData[i-gap];
//			}
//			oriData[i]=temp;
//		}
//	}
//}

//void HeapSort(std::vector<int>& oriData){
//	if(oriData.empty()) 
//		return;
//	int i=((oriData.size()-1)-1)/2;
//	for(;i>=0;i--){
//		int child;
//		int temp=oriData[i];
//		for(;i*2+1<=oriData.size()-1;i=child){
//			child=i*2+1;
//			if(child!=oriData.size()-1&&oriData[child+1]<oriData[child]){
//				child++;
//			}
//			if(oriData[child]<temp){
//				oriData[i]=oriData[child];
//			}else
//				break;
//		}
//		oriData[i]=temp;
//	}
//	for(int k=oriData.size()-1;k>1;k--){
//		int tempZ=oriData[0];
//		oriData[0]=oriData[k];
//		int child;
//		int temp=oriData[0];
//		int i=0;
//		for(;i*2+1<=k;i=child){
//			child=i*2+1;
//			if(child!=k&&oriData[child+1]<oriData[child]){
//				child++;
//			}
//			if(oriData[child]<temp){
//				oriData[i]=oriData[child];
//			}else
//				break;
//		}
//		oriData[i]=temp;
//		oriData[k]=tempZ;
//	}
//}

//void mergeSort(std::vector<int>& oriData){
//	std::vector<int> tempArray(oriData.size());
//	mergeSort(oriData,tempArray,0,oriData.size()-1);
//}

//void mergeSort(std::vector<int>& oriData,std::vector<int>& tempArray,int left,int right){
//	if(left<right){
//		int center=(left+right)/2;
//		mergeSort(oriData,tempArray,left,center);
//		mergeSort(oriData,tempArray,center+1,right);
//		merge(oriData,tempArray,left,center+1,right);
//	}
//}

//void merge(std::vector<int>& oriData,std::vector<int>& tempArray,int leftPos,int rightPos,int rightEnd){
//	int leftEnd=rightPos-1;
//	int tempPos=leftPos;
//	int numElement=rightEnd-leftPos+1;
//	while(leftPos<=leftEnd&&rightPos<=rightEnd){
//		if(oriData[leftPos]<=oriData[rightPos]){
//			tempArray[tempPos++]=oriData[leftPos++];
//		}else{
//			tempArray[tempPos++]=oriData[rightPos++];
//		}
//	}
//	while(leftPos<=leftEnd)
//		tempArray[tempPos++]=oriData[leftPos++];
//	while(rightPos<=rightEnd){
//		tempArray[tempPos++]=oriData[rightPos++];
//	}
//	for(int i=0;i<numElement;i++,rightEnd--){
//		oriData[rightEnd]=tempArray[rightEnd];
//	}
//}

//void QuickSort(std::vector<int>& oriData){
//	QuickSort(oriData,0,oriData.size()-1);
//}

//void QuickSort(std::vector<int>& oriData,int left,int right){
//	if(left+10<=right){
//		int pivot=median3(oriData,left,right);
//		int i=left,j=right-1;
//		while(true){
//			while(oriData[++i]<pivot){}
//			while(pivot<oriData[--j]){}
//			if(i<j)
//				std::swap(oriData[i],oriData[j]);
//			else
//				break;
//		}
//		std::swap(oriData[i],oriData[right-1]);
//		QuickSort(oriData,left,i-1);
//		QuickSort(oriData,i+1,right);
//	}else{
//		for(int p=left;p<=right;p++){
//			int temp=oriData[p];
//			int j=p;
//			for(;j>0&&temp<oriData[j-1];j--){
//				oriData[j]=oriData[j-1];
//			}
//			oriData[j]=temp;
//		}
//	}
//}

//int median3(std::vector<int>& oriData,int left,int right){
//	int center=(left+right)/2;
//	if(oriData[center]<oriData[left])
//		std::swap(oriData[center],oriData[left]);
//	if(oriData[right]<oriData[left])
//		std::swap(oriData[right],oriData[left]);
//	if(oriData[right]<oriData[center])
//		std::swap(oriData[center],oriData[right]);
//	std::swap(oriData[center],oriData[right-1]);
//	return oriData[right-1];
//}