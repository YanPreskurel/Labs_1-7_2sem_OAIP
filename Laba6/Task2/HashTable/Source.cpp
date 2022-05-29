#include <iostream>
#include "HashTable.h"
#include <vector>

int main() {
	HashTable<int> a;
	a.insert(3, 54);
	a.deleteByKey(3);
	std::cout << " ij " << a.empty();
	return 0;
}