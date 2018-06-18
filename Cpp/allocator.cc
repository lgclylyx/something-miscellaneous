#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class _Ty>
struct Allocator_base{
	typedef _Ty value_type;
};

template<class _Ty>
struct Allocator_base<const _Ty>{
	typedef _Ty value_type;
};

template<class _Ty>
class Allocator:public Allocator_base<_Ty>{
public:
	typedef typename std::size_t size_type;
	typedef typename std::ptrdiff_t difference_type;
	typedef _Ty* pointer;
	typedef const _Ty* const_pointer;
	typedef _Ty& reference;
	typedef const _Ty& const_reference;
	typedef Allocator_base<_Ty> _Mybase;
	typedef typename Allocator<_Ty>::value_type value_type;
	
	template<class U>
	struct rebind{
		typedef Allocator<U> other;
	};
	Allocator() throw(){}
	Allocator(const Allocator&)throw(){}
	template<class otherall>
	Allocator(const Allocator<otherall>&)throw(){}
	
	~Allocator()throw(){}

	pointer allocate(size_type num, typename Allocator<_Ty>::const_pointer hint = 0){
		static int i = 0;
		i++;
		cout << endl;
		cout << "第 "<< i << " 次分配内存空间。";
		cout << endl;
		cout << "本次分配可容纳 "<< num << " 个元素的空间。";
		cout << endl << endl;
		return (pointer)::operator new(num*sizeof(_Ty));//单纯分配空间
	}

	void construct(pointer p, const_reference value){
		new(p)_Ty(value);//调用构造函数
	}

	void destroy(pointer p){
		p->~_Ty();//析构
	}

	void deallocate(pointer p,size_type n){
		::operator delete(p);//释放空间
	}
};

template<typename T>
void print(vector<T,Allocator<T>>& iv){
	cout << "capacity: "<< iv.capacity();
	cout << "   size: " << iv.size()<< endl;
	cout << "element: ";
	for_each(iv.begin(),iv.end(),[](int n){cout << " " << n;});
	cout << endl << endl;
}

int main(){
	vector<int,Allocator<int>> vec{1,2,3};
	print<int>(vec);
	for(int i = 1; i <= 10; i++){
		vec.push_back(10*i);
		print<int>(vec);
	}
	return 0;
}

/*
answer:
第 1 次分配内存空间。
本次分配可容纳 3 个元素的空间。

capacity: 3   size: 3
element:  1 2 3


第 2 次分配内存空间。
本次分配可容纳 6 个元素的空间。

capacity: 6   size: 4
element:  1 2 3 10

capacity: 6   size: 5
element:  1 2 3 10 20

capacity: 6   size: 6
element:  1 2 3 10 20 30


第 3 次分配内存空间。
本次分配可容纳 12 个元素的空间。

capacity: 12   size: 7
element:  1 2 3 10 20 30 40

capacity: 12   size: 8
element:  1 2 3 10 20 30 40 50

capacity: 12   size: 9
element:  1 2 3 10 20 30 40 50 60

capacity: 12   size: 10
element:  1 2 3 10 20 30 40 50 60 70

capacity: 12   size: 11
element:  1 2 3 10 20 30 40 50 60 70 80

capacity: 12   size: 12
element:  1 2 3 10 20 30 40 50 60 70 80 90


第 4 次分配内存空间。
本次分配可容纳 24 个元素的空间。

capacity: 24   size: 13
element:  1 2 3 10 20 30 40 50 60 70 80 90 100

*/

/*
通过实现自己的内存分配器，可以观察容器的内存分配策略
*/
