#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include "Thread_Pool.h"

void print(const std::string& str) {
	std::cout << "current thread id: " << std::this_thread::get_id() << ". str: " << str << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

class Print1 {
public:
	void print(const std::string& str, int i) {
		std::cout << "Print1 str: " << str << ". i: " << i << std::endl;
	}
};

class Print2 {
public:
	void operator()(const std::string& str, int i) {
		std::cout << "Print2 str: " << str << ". i: " << i << std::endl;
	}
};

int main() {
	Print1 print1;
	Print2 print2;
	ThreadPool threadPool;
	threadPool.Init_Thread_Num(10);
	std::string str = "hello,world!";
	for (int i = 0;i < 10;i++) {
		threadPool.Add_Task([str] {std::cout << "lambdl: " << str << std::endl;});
		threadPool.Add_Task(print, str);
		threadPool.Add_Task(print2, str, i);
		threadPool.Add_Task(&Print1::print, &print1, str, i);
	}
	system("pause");
	return 0;
}