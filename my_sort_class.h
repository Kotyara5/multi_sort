#pragma once
#include <iostream>
#include <thread>

template <class T, int mt = 1>
class Sort {
private:
	int max_threads{ mt / 2 }; //Максимальное количество потоков (Счётчик считает пары открытых потоков) 
	int act_threads{ 0 }; //Количество активных потоков
public:
	void setMaxThreads(int mt) {
		max_threads = mt;
	}
	void my_sort(T arr[], int length) {
		quicksort(arr, 0, length - 1);
	}
private:
	void quicksort(T arr[], int low, int high) {
		if (low < high) {
			int p = partition(arr, low, high);
			if (act_threads >= max_threads) { //Если нет свободных потоков, то выполнить обе сортировки в данном
				quicksort(arr, low, p);
				quicksort(arr, p + 1, high);
			}
			else //Иначе запустить сортировку в разных потоках 
			{
				++act_threads;
				std::thread lt(&Sort::quicksort, this, arr, low, p);
				std::thread rt(&Sort::quicksort, this, arr, p + 1, high);
				lt.join();
				rt.join();
				--act_threads;
			}
		}
	}
	int partition(T arr[], int low, int high) {
		auto pivot = (arr[low] + arr[high]) / 2;
		int i = low - 1;
		int j = high + 1;
		while (true) {
			do i = i + 1;
			while (arr[i] < pivot);

			do j = j - 1;
			while (arr[j] > pivot);

			if (i >= j) return j; 

			auto tmp = std::move(arr[i]);
			arr[i] = std::move(arr[j]);
			arr[j] = std::move(tmp);
		}
	}
};
