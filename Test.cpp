#include <iostream>
#include <algorithm> // для std::sort()
#include "Timer.h"
#include "my_sort_class.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	const long S = 1000000; //Размер массивов
	const int Q = 5; //Количество тестов
	const int MT = 4; //Максимальное количество потоков (Указать чётное количество) 

	Sort<double> singleSort; 
	Sort<double, MT> multiSort;

	double* arr_std = new double[S];
	double* arr_single = new double[S];
	double* arr_thr = new double[S];

	for (int k = 0; k < Q; ++k) { //Несколько тестов
		for (int i = 0; i < S; ++i) //Заполнить массивы случайными значениями 
		{
			arr_std[i] = arr_single[i] = arr_thr[i] = (rand() % 1000000) / 1000.0;
		}

		std::cout << "std::sort" << std::endl;
		Timer t;
		std::sort(arr_std, arr_std + S);
		std::cout << "time: " << std::fixed << t.elapsed() << std::endl;

		std::cout << "single sort" << std::endl;
		t.reset();
		singleSort.my_sort(arr_single, S);
		std::cout << "time: " << std::fixed << t.elapsed() << std::endl;

		std::cout << "multi sort" << std::endl;
		t.reset();
		multiSort.my_sort(arr_thr, S);
		std::cout << "time: " << std::fixed << t.elapsed() << std::endl;

		//Проверка совпадения отсортированных массивов
		for (int i = 0; i < S; ++i) {
			if (arr_single[i] != arr_std[i]) {
				std::cout << "arrays std::sort and single sort are NOT equal" << std::endl;
				break;
			}
			if (i == S - 1 && arr_single[i] == arr_std[i])
				std::cout << "arrays std::sort and single sort are equal!" << std::endl;
		}
		for (int i = 0; i < S; ++i) {
			if (arr_thr[i] != arr_single[i]) {
				std::cout << "arrays single sort and multi sort are NOT equal" << std::endl;
				break;
			}
			if (i == S - 1 && arr_thr[i] == arr_single[i])
				std::cout << "arrays single sort and multi sort are equal!" << std::endl;
		}
		std::cout << std::endl; //Пропуск строки между тестами
	}
	delete[] arr_std;
	delete[] arr_single;
	delete[] arr_thr;
}