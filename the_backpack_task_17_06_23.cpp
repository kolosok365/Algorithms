#include <iostream>
#include <Windows.h>
#include <vector>
#include <list>
#include <conio.h>
#include <array>
#include <iomanip>

struct Column_Things
{
	std::string thing;
	int weight;
	int value;
};

struct Cell
{
	int sumvalue;
	std::list<std::string> things;
	Cell() {//обязательно нужно объявить свой конструктор по умолчанию, а то не создастся tabl
		sumvalue = 0;
		std::list<std::string>t;
		things = t;
	}
	Cell(int s, std::list<std::string>t) {
		sumvalue = s;
		things = t;
	}
};

void Show(Cell** m, int rows, int cols) {
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			std::cout << m[r][c].sumvalue << " ";
		}
		std::cout << "\n";
	}
}

void ShowThings(std::vector<Column_Things>& vt) {
	std::cout << std::setw(12) << std::left << "|Предмет" << std::setw(12) << "|Вес" << std::setw(12) << "|Стоимость" << "|\n";
	std::cout << "|" << std::string(35, '-') << "|" << std::endl;

	for (auto var : vt) {
		std::cout << "|" << std::setw(11) << std::left << var.thing << "|"
			<< std::setw(11) << std::left << var.weight << "|"
			<< std::setw(11) << std::left << var.value << "|\n";
	}
	std::cout << "\n\n";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<int> Weight{ 1,2,3,4,5,6 };
	std::vector<Column_Things> Things = { {"Вода", 3, 10},{"Книга", 1, 3},{"Еда", 2, 9},{"Куртка", 2, 5},{"Камера", 1, 6} };
	
	//std::vector<Column_Things> Things;

	/*while (true) {
	   Column_Things cur;
	   std::cout << "Введите название предмета, вес и стоимость: ";
	   std::cin >> cur.thing >> cur.weight >> cur.value;
	   Things.push_back(cur);
	   std::cout << "Добавить ещё вещь?(д/н)\n\n";
	   char ans = _getch();
	   if (ans != 'д') {
		  system("CLS");
		  break;
	   }
	}*/

	ShowThings(Things);

	Cell cur_cell;
	std::list<std::string> list_in_cell;
	const int cols = Weight.size();
	const int rows = Things.size();

	Cell** matr = new Cell * [rows];
	for (int i = 0; i < rows; ++i) {
		matr[i] = new Cell[cols];
	}

	for (int col = 0; col < Weight.size(); ++col) {//в первой строке не могу обращаться к строке выше,так как
		if (Things[0].weight <= Weight[col]) {       //её нет.Чтобы не делать постоянно проверку в цикле первая строка или нет 
			cur_cell.sumvalue = Things[0].value;       //решил заполнить первую строку в отдельном цикле
			cur_cell.things.push_back(Things[0].thing);
			matr[0][col] = cur_cell;
		}
	}

	for (int i = 1; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {

			cur_cell.sumvalue = 0;
			cur_cell.things.clear();

			if ((Things[i].weight <= Weight[j])) {
				if (j == 0 || (j - Things[i].weight == -1)) {
					if (Things[i].value > matr[i - 1][j].sumvalue) {
						cur_cell.sumvalue = Things[i].value;
						cur_cell.things.push_back(Things[i].thing);
						matr[i][j] = cur_cell;
					}
					else {
						matr[i][j] = matr[i - 1][j];
					}
				}
				else {
					if (j + 1 - Things[i].weight >= 0) {
						int max_last_add_value = matr[i - 1][j - Things[i].weight].sumvalue;//j+1 это вес рюкзака в данном столбце
						if ((Things[i].value + max_last_add_value) > matr[i - 1][j].sumvalue) {
							cur_cell.sumvalue = Things[i].value + max_last_add_value;
							cur_cell.things = (matr[i - 1][j - Things[i].weight].things);//j+1 это вес рюкзака в данном столбце
							cur_cell.things.push_back(Things[i].thing);
							matr[i][j] = cur_cell;
						}
						else {
							matr[i][j] = matr[i - 1][j];
						}
					}
					else {
						cur_cell.sumvalue = Things[i].value;
						cur_cell.things.push_back(Things[i].thing);
						matr[i][j] = cur_cell;
					}
				}
			}
			else {
				matr[i][j] = matr[i - 1][j];
			}
		}
	}

	Show(matr, rows, cols);
	std::cout << "Оптимальный набор ценой " << matr[rows - 1][cols - 1].sumvalue << " и вещами ";

	for (auto i : cur_cell.things) {
		std::cout << i << " ";
	}

	std::cout << "\n";

	for (int i = 0; i < rows; i++) {
		delete[] matr[i];
	}
	delete[] matr;

}
