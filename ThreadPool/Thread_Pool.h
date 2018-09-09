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
	Thread_vec:ָ��Thread���������ָ�������
	*/
	std::vector<Work_Task_Ptr> Thread_vec;
	/*
	�൱���ź���������ͬ���뻥��
	A condition variable is an object able to block the calling thread until notified to resume.
	It uses a unique_lock (over a mutex) to lock the thread when one of its wait functions is called. The thread remains blocked until woken up by another thread that calls a notification function on the same condition_variable object.
	Objects of type condition_variable always use unique_lock<mutex> to wait: for an alternative that works with any kind of lockable type, see condition_variable_any
	condition_variable��5������������������Ӧ�Ĺ������£�
	wait�����Լ����ȴ�����
	wait_for�����Լ����ȴ����ѣ����ȴ�һ��ʱ��
	wait_until�����Լ����ȴ����ѣ����ȴ���ĳ��ʱ���
	notify_one ����һ���ȴ���������������ϵ��߳�
	notify_all �������еȴ���������������ϵ��߳�
	*/
	std::condition_variable Task_Put;
	std::condition_variable Task_Get;
	/*
	mutex:�����������ڶ��̷߳����¼�����ʱ�Ļ���
	*/
	std::mutex Task_Queue_Mutex;
	std::queue<Task_t> Task_Queue;
	/*
	atomic:ԭ�Ӳ���������̶߳�ͬһ��Դ���з���ʱ���ܹ�ȷ��ͬʱֻ��һ���߳��ܹ����ʵ���Դ
	��Is_Stop_ThreadPool����Ϊatomic<bool>��ʾ������߳�ͬʱ������ֵʱ��ֻ��һ���ܹ���ȡ��ԭ�Ӳ����ĺô���
	�ܹ�����������ʹ��mutux��������£�ʵ�ֶ��̶߳�ȫ����Դ����ȷ���ʣ��������
	*/
	std::atomic<bool> Is_Stop_ThreadPool;
	/*
	once_flag:copy construct��operator=���ã�once_flag�൱��һ������ʹ�������̶߳���������ȴ���ֻ��һ���߳�����ִ�С�������߳��׳��쳣����ô�ӵȴ��е��߳���ѡ��һ�����ظ���������̡�
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
		ͨ��makeshared����ָ��thread���������ָ�룬ͨ��bind������this->Run_TaskתΪfunction����Ȼ������Ϊthread�����ִ�е�Ԫ��
		�൱�ڣ� function<void()> func=bind(&ThreadPool:Run_Task,this);
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
		���ٽ���������¼�������ס�ٽ���������¼������������������Լ����ȴ������߳����Ѻ󣬷���֪ͨ��Ȼ���¼������¼�����
		��Ȼ��֪ͨ����������
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
	���ر��̳߳ص��ź���Ϊtrue��Ȼ��������еȴ��е������̣߳���ΪIs_Stop_ThreadPool,�����̶߳����˳�ִ�С�
	Ȼ���������ִ���̳߳��е��̣߳������join,��join���ȴ���ִ����ɡ�Ȼ�����ִ���߳����顣Ȼ���������
	�¼����С�
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
			Task_Put.notify_one();//�����task�Ĳ���ͬ��
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
		lambda������[captured](arguments)mutable->return-type{};
		*/
		Task_t task = [&function, Args...]{ return function(Args...); };
		Add_Task_Impl(task);
	}
}

/*
  SFINAE������ƥ��ʧ�ܲ���һ�ִ���ר�����ñ�����ƥ��ʧ�����ﵽĳ��Ŀ�ĵļ��ɡ�
  enable_if:���Բ���һ���ض��ķ������ͣ�ʹ�ÿ���ģ�庯����ƥ�䡣
  ���к���ģ����ʵ�����Ĺ����У����ģ�����Function����һ���࣬��std::enable_if<std::is_class<Function>::value>::type�����һ����Ч�ķ���ֵ���ͣ�����SFINAE�����Ĵ��ڣ���
  ���ᱨ��ֻ�ǽ���Ч�ķ���ֵ����������ʵ�������ؾ�����ȥ�����������Function����һ�����ͣ��򲻻�ƥ�����������
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
