
#include <iostream>
#include <algorithm>
#include <list>
#include <typeinfo>
#include <vector>

template<typename T>
void Init(T& var)
{
	for (int i = 0; i < 30; i++) {
		var.push_back(rand() % 50);
	}

}

template<typename T>
void binary_search(std::list<T>& ml, T find_num)
{
	int low = 0;
	int high = ml.size();
	std::list<int>::iterator mid;

	while (low <= high) {
		int mid_index = (high + low) / 2;
		mid = ml.begin();
		std::advance(mid, mid_index);//ставит итератор в подсчитанную середину. list не поддерживает обращение к элементу через []

		if (find_num == *mid) {
			std::cout << "\nЧисло " << find_num << " найдено в позиции " << mid_index + 1;
			return;
		}
		else if (find_num < *mid) {
			high = mid_index - 1;
		}
		else if (find_num > *mid) {
			low = mid_index + 1;
		}
	}
	std::cout << "\nЧисло " << find_num << " не найдено!";
}

int main()
{
	setlocale(LC_ALL, "rus");
	std::list<int> m;
	Init(m);
	m.sort();
	m.erase(std::unique(std::begin(m), std::end(m)), std::end(m));

	for (auto i : m)
		std::cout << i << " ";
	std::cout << "\nВведите число, которое надо найти:";
	int num;
	std::cin >> num;

	binary_search(m,num);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
