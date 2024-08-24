#pragma once

#include <future>
#include <mutex>

#include "rhandler.h"

class QuickSort{
public:
    void swap(int& x, int& y);
    void quicksort_f(std::vector<int>& vec, int left, int right, std::shared_ptr<std::promise<void>> promise);
    void quicksort(std::vector<int>& vec, int left, int right);
    int partition(std::vector<int>& vec, int left, int right);
private:
	bool make_thread{true};
};
