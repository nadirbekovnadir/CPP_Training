#include <iostream>
#include <string>
#include <stdint.h>
#include <stdio.h>

#include <cstdlib>
#include <ctime>

uint64_t get_hash(const std::string& s, int table_size);


const int tableSize = 280000;
const int strSize = 1000;

uint32_t keys[strSize];
uint32_t init_h;

int main()
{
	srand(time(0));

	for (int i = 0; i < strSize; ++i)
	{
		keys[i] = rand();
		keys[i] = keys[i] == 0 ? 1 : keys[i];
	}

	init_h = rand();
	init_h = init_h == 0 ? 1 : init_h;

	std::string val;
	val.reserve(strSize);

	int n = 0;
	std::getline(std::cin, val);
	n = atoi(val.substr(0, val.size()).c_str());

	uint32_t hashP = 0;

	uint8_t* hash = new uint8_t[tableSize];
	for (int i = 0; i < tableSize; ++i)
		hash[i] = 0;

	int k = 0;
	int offset = 0;
	int index = 0;
	for (int i = 0; i < n; ++i)
	{
		std::getline(std::cin, val);

		hashP = get_hash(val, tableSize * 8 + 1);

		index = hashP / 8;
		offset = hashP % 8;
		if ((hash[index] & (1 << offset)) == 0)
		{
			++k;
			hash[index] |= 1 << offset;
		}
	}

	std::cout << k;
}

uint64_t get_hash(const std::string& s, int table_size)
{
	uint64_t hash_result = init_h;

	for (int i = 0; i < s.size(); ++i)
		hash_result = (keys[i] * hash_result + (uint8_t)s[i]) % table_size;

	return (hash_result <= 0) ? (hash_result + table_size) : hash_result;
}