#pragma once
#include "tpool.h"

class RequestHandler{
public:
    RequestHandler();
    ~RequestHandler();
	//void pushRequest(FuncType f, int id, int arg);
	template<typename F, typename... Args> void pushRequest(F&& f, Args&&... args);
private:
	OptimizedThreadPool m_tpool;
};

template<typename F, typename... Args>
void RequestHandler::pushRequest(F&& f, Args&&... args){
	m_tpool.push_task(std::forward<F>(f), std::forward<Args>(args)...);
}
