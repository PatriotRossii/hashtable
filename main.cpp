#include "HashTable.hpp"

#include <iostream>

constexpr std::size_t N = 50011;

constexpr int key = 123192;
constexpr int value = 10;

int main() {
	HashTable<int, int, N> table;
	
	table.insert(key, 10);
	table.insert(key + N, 20);

	std::cout << table.lookup(key) << std::endl;
	table.remove(key);
	std::cout << table.lookup(key + N) << std::endl;
}
