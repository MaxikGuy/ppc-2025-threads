#pragma once

#include <vector>

namespace savchenko_m_radix_sort_seq {

class Util {
public:
	int random_int(const int min, const int max) const;
	int random_int(const int min, const int max, const int seed) const;
	std::vector<int> random_vector_int(const size_t n, const int min, const int max) const;
	std::vector<int> random_vector_int(const size_t n, const int min, const int max, const int seed) const;

	void print_arr(const std::vector<int> arr);
};
	
}
