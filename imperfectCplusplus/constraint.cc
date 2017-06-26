//在编译期检查错误
template<typename D,typename B>
struct must_have_base{
	~must_have_base(){
		void(*p)(D*,B*) = constraints;//强迫编译器评估该函数及其中的赋值语句是否有效
	}
private:
	static void constraints(D* pd,B* pb){
		pb = pd;
	}
};

template<typename T>
struct must_be_subscriptable{
	~must_be_subscriptable(){
		void(*p)(T const& T_is_not_subscriptable) = constraints;
	}
private:
	static void constraints(T const& T_is_not_subscriptable){
		sizeof(T_is_not_subscriptable[0]);
	}
};

template<typename T>
struct must_be_subscriptable_as_decayable_pointer{
	~must_be_subscriptable_as_decayable_pointer(){
		void(*p)(T const& T_is_not_subscriptable) = constraints;
	}
private:
	static void constraints(T const& T_is_not_subscriptable){
		sizeof(0[T_is_not_subscriptable]);
	}
};

template<typename T>
struct must_be_pod{
	~must_be_pod(){
		void(*p)()=constraints;
	}
private:
	static void constraints(){
		//拥有非平凡（non-trivial）的构造函数、拷贝构造函数、析构函数、赋值操作符的对象不能作为union的成员
		union{
			T T_is_not_pod_type;
		};
	}
};

template<typename T>
struct must_be_pod_or_void{
	~must_be_pod_or_void(){
		void(*p)()=constraints;
	}
private:
	static void constraints(){
		//拥有非平凡（non-trivial）的构造函数、拷贝构造函数、析构函数、赋值操作符的对象不能作为union的成员
		union{
			T T_is_not_pod_type;
		};
	}
};
template<>
struct must_be_pod_or_void<void>{

};

template<typename T>
struct size_of{
	enum {value = sizeof(T)};
};

template<>
struct size_of<void>{
	enum {value = 0};
};

template<typename T1,typename T2>
struct must_be_same_size{
	~must_be_same_size(){
		void (*p)() = constraints;
	}
private:
	static void constraints(){
		const int T1_not_same_size_as_t2 = sizeof(T1)==sizeof(T2);
		//const int T1_not_same_size_as_t2 = size_of<T1>::value==size_of<T2>::value;
		int i[T1_not_same_size_as_t2];
	}
};

template<>
struct must_be_same_size<void,void>{

};

class B{

};

class D{

};

class C:public B{

};

struct subs{
public:
	int operator[](unsigned int index) const;
};

struct not_subs{};

/*int main(){
	//must_have_base<B,D> a;		//wrong
	must_have_base<C,B> b;
	must_have_base<B,B> c;
	must_be_subscriptable<subs> d;
	must_be_subscriptable<int[]> e;
	must_be_subscriptable<int*> f;
	//must_be_subscriptable<not_subs> g;		//wrong
	//must_be_subscriptable_as_decayable_pointer<subs> h;		//wrong

}
*/
