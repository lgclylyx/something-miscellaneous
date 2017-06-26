#ifndef _index_max_pq_
#define _index_max_pq_

#include <vector>

using std::vector;

template<typename T>
class IndexMaxPQ{
public:
	IndexMaxPQ(int maxN):pqsize(0){
		eles.resize(maxN);
		pq.resize(maxN);
		qp.resize(maxN);
	}
	/*
	 * k: 元素在eles数组中的位置
	 * t: 插入元素
	 * */
	void insert(int k,const T& t){
		if(contains(k))
			return;
		pqsize++;
		qp[k] = pqsize;
		pq[pqsize] = k;
		eles[k] = t;
		swim(pqsize);
	}
	void change(int k,const T& t){
		if(!contains(k))
			return;
		eles[k] = t;
		swim(qp[k]);
		sink(qp[k]);
	}
	bool contains(int k){
		if(pqsize == 0)
			return false;
		return qp[k] != 0;
	}
	void deleteIndexk(int& k){
		if(!contains(k))
			return;
		int temp = qp[k];
		pq[temp] = pq[pqsize];
		pq[pqsize] = k;
		qp[pq[pqsize]] = 0;
		qp[pq[temp]] = k;
		pqsize--;
		swim(temp);
		sink(temp);
	}
	T max()const{
		return eles[pq[1]];
	}
	int maxIndex()const{
		return pq[1];
	}
	int delMax(){
		if(pqsize==0)
			return 0;
		int temp =pq[1];
		pq[1] = pq[pqsize--];
		sink(1);
		qp[temp] = 0;
		pq[pqsize+1] = 0;
		return temp;
	}
	bool isEmpty()const{
		return pqsize == 0;
	}
	int size()const{
		return pqsize;
	}
private:
	/*
	 * k: pq数组的下标
	 */
	void swim(int k){
		T temp = pq[k];
		while(k > 1 && (eles[pq[k/2]] < eles[temp])){
			pq[k] = pq[k/2];
			qp[pq[k/2]] = k;
			k=k/2;
		}
		pq[k] = temp;
		qp[pq[k]] = k;
	}
	void sink(int k){
		T temp = pq[k];
		while(2*k <= pqsize){
			int j = 2*k;
			if(j < pqsize && eles[pq[j]] < eles[pq[j+1]]) j++;
			if(eles[temp] < eles[pq[j]]){
				pq[k] = pq[j];
				qp[pq[j]] = k;
				k = j;
			}else
				break;
		}
		pq[k] = temp;
		qp[temp] = k;
	}
private:
	vector<T> eles;
	vector<int> pq;
	vector<int> qp;
	int pqsize;
};

#endif
