#pragma once

#include <vector>
#include <cstdint>

namespace savchenko_m_radix_sort {

class Sorter {
public:
	bool is_sorted(int* arr, size_t n) const;
	
	void radix_sort_seq(int* input, int* output, size_t n);
	void radix_sort_omp(int* input, int* output, size_t n);
	void radix_sort_tbb(int* input, int* output, size_t n);
	void radix_sort_stl(int* input, int* output, size_t n);

protected:
	uint8_t get_byte(int num, int byte_pos) const;

	void counting_sort_seq(std::vector<int>& arr, int byte_pos);
	void counting_sort_omp(std::vector<int>& arr, int byte_pos);
	void counting_sort_tbb(std::vector<int>& arr, int byte_pos);
	void counting_sort_stl(std::vector<int>& arr, int byte_pos);

};

}
