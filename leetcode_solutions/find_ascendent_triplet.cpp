#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

bool find_triplet(std::vector<int>& numbers) {
	if (numbers.size() <= 2) {
		return false;
	}
	int p1 = 0;
	int p2 = -1;

	for (size_t i = 0; i < numbers.size(); ++i) {
		if (p2 >= 0) {
			if (numbers[i] > numbers[p2]) {
				return true;
			}
			if (numbers[i] > numbers[p1]) {
				p2 = i;
			} else {
				p1 = i; // another candidate triplet
			}
		} else {
			if (numbers[i] > numbers[p1]) {
				p2 = i;
			} else {
				p1 = i;
			}
		}
	}
	return false;
}

void get_vector(std::string& line, std::vector<int>& numbers) {
	numbers.clear();
	std::stringstream ssm;
	ssm << line;
	int x;
	while (ssm >> x) {
		std::cout << x << " ";
		numbers.push_back(x);
	}
	std::cout << std::endl;
}

int main() {
	std::ifstream inf;
	inf.open("./input", std::ifstream::in);

	std::string line;
	std::vector<int> vec;
	while( std::getline(inf, line)) {
		get_vector(line, vec);
		std::cout << (find_triplet(vec) ? "True" : "False") << std::endl;
	}
	return 0;
}
