#include "omp/savchenko_m_radix_sort/include/sorter.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <omp.h>

#include <iostream>
#include <chrono>

bool savchenko_m_radix_sort_omp::Sorter::is_sorted(int* arr, size_t n) const{
	if (n <= 0) {
		throw std::out_of_range("ERROR: n must be greater than 0");
	}
	if (arr == nullptr) {
		throw std::invalid_argument("ERROR: arr should not be NULL");
	}
	
	bool flag = true;
	#pragma omp parallel for shared(flag)
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			#pragma omp critical
			flag = false;
			break;
		}
	}

	return flag;
}

int savchenko_m_radix_sort_omp::Sorter::get_bit(int num, int bit_pos) {
	return (num >> bit_pos) & 1;
}

// SEQ

void savchenko_m_radix_sort_omp::Sorter::radix_sort_seq(int* input, int* output, size_t n) {
	// validation
	if (n <= 0) {
		throw std::out_of_range("ERROR: n must be greater than 0");
	}
	if (input == nullptr) {
		throw std::invalid_argument("ERROR: input should not be NULL");
	}
	if (output == nullptr) {
		throw std::invalid_argument("ERROR: output should not be NULL");
	}

	// pre processing
	size_t pos_count = 0;
	size_t neg_count = 0;
	for (size_t i = 0; i < n; i++) {
		int num = input[i];
		if (num < 0) {
			neg_count++;
		}
		else {
			pos_count++;
		}
	}

	std::vector<int> negatives(neg_count);
	std::vector<int> positives(pos_count);
	size_t pos_ind = 0;
	size_t neg_ind = 0;
	for (size_t i = 0; i < n; i++) {
		int num = input[i];
		if (num < 0) {
			negatives[neg_ind++] = -num;
		}
		else {
			positives[pos_ind++] = num;
		}
	}

	// radix sort
	const int bit_count = sizeof(int) * 8;
	if (!negatives.empty()) {
		for (int bit_pos = 0; bit_pos < bit_count; bit_pos++) {
			counting_sort_seq(negatives, bit_pos);
		}
		std::reverse(negatives.begin(), negatives.end());
		for (size_t i = 0; i < neg_count; i++) {
			negatives[i] = -negatives[i];
		}
	}

	if (!positives.empty()) {
		for (int bit_pos = 0; bit_pos < bit_count; bit_pos++) {
			counting_sort_seq(positives, bit_pos);
		}
	}


	// post processing
	std::copy(negatives.begin(), negatives.end(), output);
	std::copy(positives.begin(), positives.end(), output + negatives.size());
}

void savchenko_m_radix_sort_omp::Sorter::counting_sort_seq(std::vector<int>& arr, int bit_pos) {
	size_t n = arr.size();
	std::vector<int> output(n);
	std::vector<int> count(2, 0);

	for (size_t i = 0; i < n; i++) {
		int num = arr[i];
		int bit = get_bit(num, bit_pos);
		count[bit]++;
	}
	
	count[1] += count[0];

	for (size_t i = n; i > 0; i--) {
		size_t ind = i - 1;
		int num = arr[ind];
		int bit = get_bit(num, bit_pos);
		output[count[bit] - 1] = num;
		count[bit]--;
	}

	arr = output;
}

// OMP

void savchenko_m_radix_sort_omp::Sorter::radix_sort_omp(int* input, int* output, size_t n) {
	// validation
	if (n <= 0) {
		throw std::out_of_range("ERROR: n must be greater than 0");
	}
	if (input == nullptr) {
		throw std::invalid_argument("ERROR: input should not be NULL");
	}
	if (output == nullptr) {
		throw std::invalid_argument("ERROR: output should not be NULL");
	}

	// pre processing
	size_t pos_count = 0;
	size_t neg_count = 0;
	#pragma omp parallel for reduction(+:pos_count, neg_count) schedule(static)
	for (int i = 0; i < n; i++) {
		if (input[i] < 0) {
			neg_count++;
		}
		else {
			pos_count++;
		}
	}

	std::vector<int> negatives(neg_count);
	std::vector<int> positives(pos_count);
	size_t pos_ind = 0;
	size_t neg_ind = 0;
	for (int i = 0; i < n; i++) {
		int num = input[i];
		if (num < 0) {
			negatives[neg_ind] = -num;
			neg_ind++;
		}
		else {
			positives[pos_ind] = num;
			pos_ind++;
		}
	}

	// radix sort
	const int bit_count = sizeof(int) * 8 - 1;
	#pragma omp parallel sections shared(positives, negatives, bit_count, pos_count, neg_count)
	{
		#pragma omp section 
		{
			if (!negatives.empty()) {
				for (int bit_pos = 0; bit_pos < bit_count; bit_pos++) {
					counting_sort_seq(negatives, bit_pos);
				}
				std::reverse(negatives.begin(), negatives.end());
				for (int i = 0; i < neg_count; i++) {
					negatives[i] = -negatives[i];
				}
			}
		}

		#pragma omp section 
		{
			if (!positives.empty()) {
				for (int bit_pos = 0; bit_pos < bit_count; bit_pos++) {
					counting_sort_seq(positives, bit_pos);
				}
			}
		}
	}


	// post processing
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			if (!negatives.empty()) {
				std::copy(negatives.begin(), negatives.end(), output);
			}
		}

		#pragma omp section
		{
			if (!positives.empty()) {
				std::copy(positives.begin(), positives.end(), output + negatives.size());
			}
		}
	}
}

void savchenko_m_radix_sort_omp::Sorter::counting_sort_omp(std::vector<int>& arr, int bit_pos) {
	size_t n = arr.size();
	std::vector<int> output(n);
	std::vector<int> count(2, 0);

	int count_0 = 0, count_1 = 0;
	#pragma omp parallel for reduction(+:count_0, count_1) schedule(static)
	for (int i = 0; i < n; i++) {
		int bit = get_bit(arr[i], bit_pos);
		if (bit == 0) {
			count_0++;
		}
		else {
			count_1++;
		}
	}
	count[0] = count_0;
	count[1] = count_1 + count_0;

	#pragma omp parallel for schedule(static)
	for (int i = n - 1; i >= 0; i--) {
		int bit = get_bit(arr[i], bit_pos);

		#pragma omp critical
		{
			output[count[bit] - 1] = arr[i];
			count[bit]--;
		}
	}

	arr = output;
}

// TBB

void savchenko_m_radix_sort_omp::Sorter::radix_sort_tbb(int* input, int* output, size_t n) {

	throw "NOT IMPLEMENTED";
}

void savchenko_m_radix_sort_omp::Sorter::counting_sort_tbb(std::vector<int>& arr, int bit_pos) {

	throw "NOT IMPLEMENTED";
}
