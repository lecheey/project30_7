#include <iostream>
#include <future>
#include <chrono>
#include <random>
#include <vector>

#include "qsort.h"

QuickSort qSort;

int main(){
	std::cout << "Генерирую массив...";
	srand(0);
	long arr_size = 100000000;
	std::vector<int> array;
	for(long i = 0; i < arr_size; i++) {
		array.push_back(rand() % 500000);
	}
	std::cout << "успешно" << std::endl;

	time_t start, end;
	
	std::cout << "Сортирую..." << std::endl;
	
	time(&start);
	qSort.quicksort(array, 0, arr_size);
	time(&end);
	
	std::cout << "успешно" << std::endl;

	double seconds = difftime(end, start);
	printf("The time: %f seconds\n", seconds);
	
	return 0;
}
