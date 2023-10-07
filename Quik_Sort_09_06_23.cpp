
#include <iostream>
#include <vector>
#include <iterator>
#include <Windows.h>

#include <stdio.h> 
#include <time.h> 

void Show(const std::vector<int>& v) {
	for (auto i : v)
		std::cout << i << " ";
	std::cout << "\n";
}

std::vector<int> SortQuik(std::vector<int> sv, int ib, int ie) {
	if (sv.size() < 2)
		return sv;
	std::vector<int> left;
	std::vector<int> right;

	int pivot = sv[ib];//опорный элемент
	std::vector<int>::iterator current = sv.begin() + ib;
	current++;
	while (ib < ie) {
		if (pivot >= *current) {
			left.push_back((*current));
		}
		else {
			right.push_back((*current));
		}
		current++;
		ib++;
	}
	left = SortQuik(left, 0, left.size() - 1);
	right = SortQuik(right, 0, right.size() - 1);
	left.insert(left.end(), pivot);
	left.insert(left.end(), right.begin(), right.end());
	return left;
}

void SortBuble(std::vector<int>& sv, int ib, int ie) {
	for (; ib <= ie; ++ib) {
		for (int j = ib + 1; j <= ie; ++j) {
			if (sv[j] < sv[ib]) {
				std::swap(sv[j], sv[ib]);
			}
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	clock_t start;
	clock_t end;
	double seconds;
	std::vector<int> mv;
	int vector_size = 50;
	for (int i = 0; i < vector_size; ++i)
		mv.push_back(i * 5);

	for (int i = 0; i < vector_size; ++i) {//перемешиваю массив СНАЧАЛА ПУЗЫРЕК РАБОТАЕТ БЫСТРЕЕ,Т.К НЕТ РЕКУРСИИ,
		std::swap(mv[i], mv[rand() % (mv.size())]);// НО КОГДА ЭЛЕМЕНТОВ СТАНОВИТСЯ БОЛЬШЕ БЫСТРАЯ СОРТИРОВКА СТАНОВИТСЯ НАМНОГО БЫСТРЕЕ
	}
	std::cout << "1-ый вектор: ";
	Show(mv);
	std::cout << "\n2-ой вектор: ";
	std::vector<int> mv2;//второй неотсортированный вектор для сортировки пузырьком 
	mv2 = mv;
	Show(mv2);

	std::cout << "\n1-ый отсортированный быстрой сортировкой вектор за время: ";
	start = clock();
	mv = SortQuik(mv, 0, mv.size() - 1);
	end = clock();
	seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << seconds << "\n";
	Show(mv);

	std::cout << "\n2-ой отсортированный пузырьком вектор за время: ";
	start = clock();
	SortBuble(mv2, 0, mv2.size() - 1);
	end = clock();
	seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << seconds << "\n";
	Show(mv2);

}

