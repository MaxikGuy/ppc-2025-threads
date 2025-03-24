#include "seq/savchenko_m_radix_sort/include/sorter.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>

bool savchenko_m_radix_sort_seq::Sorter::is_sorted(int* arr, size_t n) const{
	if (n <= 0) {
		throw std::out_of_range("ERROR: n must be greater than 0");
	}
	if (arr == nullptr) {
		throw std::invalid_argument("ERROR: arr should not be NULL");
	}
	
	bool flag = true;
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			flag = false;
			break;
		}
	}

	return flag;
}

int savchenko_m_radix_sort_seq::Sorter::get_bit(int num, int bit_pos) {
	return (num >> bit_pos) & 1;
}

// SEQ

void savchenko_m_radix_sort_seq::Sorter::radix_sort_seq(int* input, int* output, size_t n) {
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

void savchenko_m_radix_sort_seq::Sorter::counting_sort_seq(std::vector<int>& arr, int bit_pos) {
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

void savchenko_m_radix_sort_seq::Sorter::radix_sort_omp(int* input, int* output, size_t n) {

	throw "NOT IMPLEMENTED";
}

void savchenko_m_radix_sort_seq::Sorter::counting_sort_omp(std::vector<int>& arr, int exp) {

	throw "NOT IMPLEMENTED";
}

// TBB

void savchenko_m_radix_sort_seq::Sorter::radix_sort_tbb(int* input, int* output, size_t n) {

	throw "NOT IMPLEMENTED";
}

void savchenko_m_radix_sort_seq::Sorter::counting_sort_tbb(std::vector<int>& arr, int exp) {

	throw "NOT IMPLEMENTED";
}
