#pragma once

#include <queue>
#include <future>
#include <thread>
#include <condition_variable>
#include <vector>
#include <functional>
#include <mutex>

void taskFunc(int id, int delay);
typedef std::function<void()> task_type;
typedef void (*FuncType) (int, int);

template<class T>
class BlockedQueue{
public:
	void push(T& item){
		std::lock_guard<std::mutex> l(m_locker);
	    m_task_queue.push(item);
	    m_notifier.notify_one();
	}
	
	void pop(T& item){
		std::unique_lock<std::mutex> l(m_locker);
	    if(m_task_queue.empty())
	        m_notifier.wait(l, [this]{return !m_task_queue.empty();});
	    item = m_task_queue.front();
	    m_task_queue.pop();
	}
	
	bool fast_pop(T& item){
		std::lock_guard<std::mutex> l(m_locker);
    	if(m_task_queue.empty())
    	    return false;
    	item = m_task_queue.front();
    	m_task_queue.pop();
    	return true;
	}

private:
    std::mutex m_locker;
    std::queue<T> m_task_queue; // очередь задач
    std::condition_variable m_notifier; // уведомитель
};

class OptimizedThreadPool{
   public:
       OptimizedThreadPool();
       void start();
       void stop();
	   template<typename F, typename... Args> void push_task(F&& f, Args&&... args); 
       void threadFunc(int qindex);
   private:
       int m_thread_count;
       int m_index;

       std::vector<std::thread> m_threads;
       std::vector<BlockedQueue<task_type>> m_thread_queues; // вектор очередей
};

template<typename F, typename... Args>
void OptimizedThreadPool::push_task(F&& f, Args&&... args){
	int queue_to_push = m_index++ % m_thread_count;
	task_type new_task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
	m_thread_queues[queue_to_push].push(new_task);
}
