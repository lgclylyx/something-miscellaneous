#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <type_traits>
#include <string>

static const std::size_t MAX_TASK_QUEUE_SIZE = 10000;
static const std::size_t MAX_THREAD_SIZE = 30;

class ThreadPool
{
public:
	using Work_Task_Ptr = std::shared_ptr<std::thread>;
	using Task_t = std::function<void()>;
	explicit ThreadPool();
	~ThreadPool();
	void Init_Thread_Num(std::size_t num);
	template<typename Function, typename ...args>
	void Add_Task(const Function& function, args... Args);
	template<typename Function, typename ...args>
	typename std::enable_if<std::is_class<Function>::value>::type Add_Task(Function& function, args... Args);
	template<typename Function, typename self, typename ...args>
	void Add_Task(const Function & function, self * Self, args ...Args);
	void Stop();
private:
	void Add_Task_Impl(const Task_t& task_t);
	void TerminateAll();
	void Run_Task();
	void Clean_Task_Queue();
private:
	/*
	Thread_vec:指向Thread对象的智能指针的数组
	*/
	std::vector<Work_Task_Ptr> Thread_vec;
	/*
	相当于信号量，用于同步与互斥
	A condition variable is an object able to block the calling thread until notified to resume.
	It uses a unique_lock (over a mutex) to lock the thread when one of its wait functions is called. The thread remains blocked until woken up by another thread that calls a notification function on the same condition_variable object.
	Objects of type condition_variable always use unique_lock<mutex> to wait: for an alternative that works with any kind of lockable type, see condition_variable_any
	condition_variable有5个函数，函数名及对应的功能如下：
	wait阻塞自己，等待唤醒
	wait_for阻塞自己，等待唤醒，最多等待一段时间
	wait_until阻塞自己，等待唤醒，最多等待到某个时间点
	notify_one 唤醒一个等待在这个条件变量上的线程
	notify_all 唤醒所有等待在这个条件变量上的线程
	*/
	std::condition_variable Task_Put;
	std::condition_variable Task_Get;
	/*
	mutex:互斥锁，用于多线程访问事件队列时的互斥
	*/
	std::mutex Task_Queue_Mutex;
	std::queue<Task_t> Task_Queue;
	/*
	atomic:原子操作，多个线程对同一资源进行访问时，能够确保同时只有一个线程能够访问到资源
	将Is_Stop_ThreadPool申明为atomic<bool>表示，多个线程同时访问其值时，只有一个能够获取。原子操作的好处是
	能够在无锁（不使用mutux）的情况下，实现多线程对全局资源的正确访问，提高性能
	*/
	std::atomic<bool> Is_Stop_ThreadPool;
	/*
	once_flag:copy construct和operator=禁用，once_flag相当于一个锁，使用它的线程都会在上面等待，只有一个线程允许执行。如果该线程抛出异常，那么从等待中的线程中选择一个，重复上面的流程。
	struct once_flag
	{
	constexpr once_flag() noexcept;
	once_flag(const once_flag&) = delete;
	once_flag& operator=(const once_flag&) = delete;
	};
	*/
	std::once_flag Call_Flag;
};

ThreadPool::ThreadPool() :Is_Stop_ThreadPool(false) {
}

ThreadPool::~ThreadPool() {
	Stop();
}

inline void ThreadPool::Init_Thread_Num(std::size_t num) {
	if (num <= 0 || num > MAX_THREAD_SIZE) {
		std::string str = "Number of threads in the range of 1 to " + std::to_string(MAX_THREAD_SIZE);
		throw std::invalid_argument(str);
	}
	for (std::size_t i = 0;i < num;i++) {
		/*
		通过makeshared创建指向thread对象的智能指针，通过bind函数将this->Run_Task转为function对象，然后将其作为thread对象的执行单元。
		相当于： function<void()> func=bind(&ThreadPool:Run_Task,this);
				 shared_ptr<thread>=makeshared<thread>(func);
				template <class Fn, class... Args>
					explicit thread (Fn&& fn, Args&&... args);
		*/
		Thread_vec.emplace_back(std::make_shared<std::thread>(std::bind(&ThreadPool::Run_Task, this)));
	}
}

inline void ThreadPool::Stop() {
	/*
	template<class Callable, class ...Args>
	void call_once(once_flag& flag, Callable&& func, Args&&... args);
	*/
	std::call_once(Call_Flag, [this] {TerminateAll();});
}

inline void ThreadPool::Add_Task_Impl(const Task_t & task_t) {
	/*
		向临界区中添加事件，先锁住临界区，如果事件队列已满，则阻塞自己，等待消费线程消费后，发送通知，然后将事件放入事件队列
		，然后通知消费者消费
	*/
	std::unique_lock<std::mutex> locker(Task_Queue_Mutex);
	while (Task_Queue.size() == MAX_TASK_QUEUE_SIZE && !Is_Stop_ThreadPool) {
		Task_Put.wait(locker);
	}
	Task_Queue.emplace(std::move(task_t));
	Task_Get.notify_one();
}

inline void ThreadPool::TerminateAll() {
	/*
	将关闭线程池的信号设为true，然后解锁所有等待中的消费线程，因为Is_Stop_ThreadPool,所有线程都会退出执行。
	然后遍历所有执行线程池中的线程，如果可join,就join，等待其执行完成。然后清空执行线程数组。然后清空所有
	事件队列。
	*/
	Is_Stop_ThreadPool = true;
	Task_Get.notify_all();
	for (auto& vec : Thread_vec) {
		if (vec != nullptr) {
			if (vec->joinable())
				vec->join();
		}
	}
	Thread_vec.clear();
	Clean_Task_Queue();
}

inline void ThreadPool::Run_Task() {
	while (true) {
		Task_t task = nullptr;
		{
			std::unique_lock<std::mutex> locker(Task_Queue_Mutex);
			while (Task_Queue.empty() && !Is_Stop_ThreadPool) {
				Task_Get.wait(locker);
			}
			if (Is_Stop_ThreadPool)
				break;
			if (!Task_Queue.empty()) {
				task = std::move(Task_Queue.front());
				Task_Queue.pop();
			}
		}
		if (task != nullptr) {
			task();
			Task_Put.notify_one();//与放入task的操作同步
		}
	}
}

inline void ThreadPool::Clean_Task_Queue() {
	std::lock_guard<std::mutex> locker(Task_Queue_Mutex);
	while (!Task_Queue.empty()) {
		Task_Queue.pop();
	}
}

template<typename Function, typename ...args>
inline void ThreadPool::Add_Task(const Function & function, args ...Args) {
	if (!Is_Stop_ThreadPool) {
		/*
		lambda函数：[captured](arguments)mutable->return-type{};
		*/
		Task_t task = [&function, Args...]{ return function(Args...); };
		Add_Task_Impl(task);
	}
}

/*
  SFINAE技术：匹配失败不是一种错误，专门利用编译器匹配失败来达到某种目的的技巧。
  enable_if:用以产生一个特定的返回类型，使得控制模板函数的匹配。
  下列函数模板在实例化的过程中，如果模板参数Function不是一个类，则std::enable_if<std::is_class<Function>::value>::type会产生一个无效的返回值类型，由于SFINAE条件的存在，则
  不会报错，只是将无效的返回值或参数的这个实例从重载决议中去掉，所以如果Function不是一个类型，则不会匹配这个函数。
*/
template<typename Function, typename ...args>
inline typename std::enable_if<std::is_class<Function>::value>::type ThreadPool::Add_Task(Function & function, args ...Args) {
	if (!Is_Stop_ThreadPool) {
		Task_t task = [&function, Args...]{ return function(Args...); };
		Add_Task_Impl(task);
	}
}

template<typename Function, typename self, typename ...args>
inline void ThreadPool::Add_Task(const Function & function, self * Self, args ...Args) {
	if (!Is_Stop_ThreadPool) {
		Task_t task = [&function, &Self, Args...]{ return(*Self.*function)(Args...); };
		Add_Task_Impl(task);
	}
}
