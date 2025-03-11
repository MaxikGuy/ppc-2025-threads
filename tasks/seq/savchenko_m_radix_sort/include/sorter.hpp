#pragma once

#include <vector>

namespace savchenko_m_radix_sort_seq {

class Sorter {
public:
	bool is_sorted(int* arr, size_t n) const;
	
	void radix_sort_seq(int* input, int* output, size_t n);
	void radix_sort_omp(int* input, int* output, size_t n);
	void radix_sort_tbb(int* input, int* output, size_t n);

protected:
	// seq
	void counting_sort_seq(std::vector<int>& arr, int exp);
	void radix_sort_positives_seq(std::vector<int>& arr);

	// omp
	void counting_sort_omp(std::vector<int>& arr, int exp);
	void radix_sort_positives_omp(std::vector<int>& arr);

	// tbb
	void counting_sort_tbb(std::vector<int>& arr, int exp);
	void radix_sort_positives_tbb(std::vector<int>& arr);

};

}
