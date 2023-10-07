
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>

std::vector<std::string> processed;
std::string Start, Finish;

std::string Lowest_Cost_Node(std::unordered_map<std::string, int> costs) {
	int lowest_cost = INT_MAX;
	std::string lowest_cost_node = "-";
	int cost;

	for (const auto [node, c] : costs) {
		cost = costs[node];
		if ((cost < lowest_cost) && (std::find(processed.begin(), processed.end(), node) == processed.end())) {
			lowest_cost = cost;
			lowest_cost_node = node;
		}
	}
	return lowest_cost_node;
}

void ShowPuth(std::unordered_map<std::string, std::string> m, std::string node, std::string parent_node) {
	if (parent_node != Start) {
		ShowPuth(m, parent_node, m[parent_node]);
		std::cout << "->" << parent_node;
	}
	else {
		std::cout << parent_node;
	}
}

void AddEdge(std::unordered_map<std::string, std::unordered_map<std::string, int>>& g, std::string s1, std::string s2, int l) {
	g[s1][s2] = l;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::unordered_map<std::string, std::unordered_map<std::string, int>> Graph;
	std::unordered_map<std::string, int> Costs;
	std::unordered_map<std::string, std::string> Parents;

	AddEdge(Graph, "1", "2", 18);
	AddEdge(Graph, "2", "1", 18);
	AddEdge(Graph, "2", "4", 27);
	AddEdge(Graph, "4", "2", 27);
	AddEdge(Graph, "1", "3", 7);
	AddEdge(Graph, "3", "1", 7);
	AddEdge(Graph, "3", "4", 360);
	AddEdge(Graph, "4", "3", 360);
	AddEdge(Graph, "3", "5", 33);
	AddEdge(Graph, "5", "6", 38);
	AddEdge(Graph, "6", "5", 38);
	AddEdge(Graph, "4", "6", 1);
	AddEdge(Graph, "6", "4", 1);


	/*AddEdge(Graph,"6", "8", 14);
	AddEdge(Graph,"8", "6", 14);
	AddEdge(Graph,"4", "8", 9);
	AddEdge(Graph,"8", "4", 9);
	AddEdge(Graph,"6", "7", 27);
	AddEdge(Graph,"7", "6", 27);
	AddEdge(Graph,"7", "12", 22);
	AddEdge(Graph,"12", "7", 22);
	AddEdge(Graph,"8", "11", 12);
	AddEdge(Graph,"11", "8", 12);
	AddEdge(Graph,"11", "12", 26);
	AddEdge(Graph,"12", "26", 24);
	AddEdge(Graph,"26", "12", 24);
	AddEdge(Graph,"26", "29", 5);
	AddEdge(Graph,"26", "27", 10);
	AddEdge(Graph,"27", "26", 10);
	AddEdge(Graph,"27", "28", 29);
	AddEdge(Graph,"28", "27", 29);
	AddEdge(Graph,"25", "27", 26);
	AddEdge(Graph,"27", "25", 26);
	AddEdge(Graph,"24", "25", 38);
	AddEdge(Graph,"25", "24", 38);
	AddEdge(Graph,"24", "28", 17);
	AddEdge(Graph,"28", "24", 17);
	AddEdge(Graph,"28", "29", 5);
	AddEdge(Graph,"29", "28", 5);
	AddEdge(Graph,"11", "29", 13);
	AddEdge(Graph,"29", "11", 13);
	AddEdge(Graph,"11", "30", 8);
	AddEdge(Graph,"30", "11", 8);
	AddEdge(Graph,"23", "24", 36);
	AddEdge(Graph,"24", "23", 36);
	AddEdge(Graph,"22", "23", 30);
	AddEdge(Graph,"23", "22", 30);
	AddEdge(Graph,"21", "23", 5);
	AddEdge(Graph,"23", "21", 5);
	AddEdge(Graph,"13", "21", 18);
	AddEdge(Graph,"21", "13", 18);
	AddEdge(Graph,"4", "9", 23);
	AddEdge(Graph,"9", "4", 23);
	AddEdge(Graph,"9", "10", 40);
	AddEdge(Graph,"10", "9", 40);
	AddEdge(Graph,"10", "30", 20);
	AddEdge(Graph,"30", "10", 20);
	AddEdge(Graph,"10", "15", 22);
	AddEdge(Graph,"15", "10", 22);
	AddEdge(Graph,"14", "15", 38);
	AddEdge(Graph,"15", "14", 38);
	AddEdge(Graph,"15", "16", 32);
	AddEdge(Graph,"16", "15", 32);
	AddEdge(Graph,"16", "17", 6);
	AddEdge(Graph,"17", "16", 6);
	AddEdge(Graph,"17", "18", 8);
	AddEdge(Graph,"18", "17", 8);
	AddEdge(Graph,"15", "18", 35);
	AddEdge(Graph,"18", "19", 26);
	AddEdge(Graph,"19", "18", 26);
	AddEdge(Graph,"19", "20", 18);
	AddEdge(Graph,"20", "19", 18);
	AddEdge(Graph,"14", "19", 6);
	AddEdge(Graph,"19", "14", 6);
	AddEdge(Graph,"20", "21", 38);
	AddEdge(Graph,"21", "20", 38);
	AddEdge(Graph,"20", "22", 17);
	AddEdge(Graph,"22", "20", 17);
	AddEdge(Graph,"14", "30", 28);
	AddEdge(Graph,"30", "14", 28);
	AddEdge(Graph,"13", "30", 26);
	AddEdge(Graph,"30", "13", 26);
	AddEdge(Graph,"16", "9", 13);
	AddEdge(Graph,"9", "16", 13);*/

	for (auto note : Graph) {
		Costs[note.first] = INT_MAX;
		Parents[note.first] = "-";
	}

	std::cout << "Введите начало: ";
	std::cin >> Start;

	int min_cost = INT_MAX;
	std::string first_neighbor = " ";
	for (auto [neighbor, cost] : Graph[Start]) {
		Parents[neighbor] = Start;
		Costs[neighbor] = cost;
		/*Costs[neighbor] = cost;
		if (cost <= min_cost) {
			first_neighbor = neighbor;
			min_cost = cost;
	   }*/
	}

	//Parents[first_neighbor] = Start;

	std::cout << "Введите конец: ";
	std::cin >> Finish;

	std::string node = Lowest_Cost_Node(Costs);
	int cost, new_cost;
	std::unordered_map<std::string, int> neighbors;
	while (node != "-") {
		cost = Costs[node];
		neighbors = Graph[node];
		for (auto n : neighbors) {
			new_cost = n.second + cost;
			if (Costs[n.first] >= new_cost) {
				Costs[n.first] = new_cost;
				Parents[n.first] = node;
			}
		}
		processed.push_back(node);
		node = Lowest_Cost_Node(Costs);
	}

	ShowPuth(Parents, Finish, Parents[Finish]);
	std::cout << "->" << Finish;
}

