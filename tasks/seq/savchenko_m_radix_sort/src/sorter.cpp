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

// SEQ

void savchenko_m_radix_sort_seq::Sorter::radix_sort_seq(int* input, int* output, size_t n) {
	if (n <= 0) {
		throw std::out_of_range("ERROR: n must be greater than 0");
	}
	if (input == nullptr) {
		throw std::invalid_argument("ERROR: input should not be NULL");
	}
	if (output == nullptr) {
		throw std::invalid_argument("ERROR: output should not be NULL");
	}

	std::vector<int> negatives;
	std::vector<int> positives;

	for (size_t i = 0; i < n; i++) {
		int val = input[i];
		if (val < 0) {
			negatives.push_back(-val);
		} else {
			positives.push_back(val);
		}
	}

	if (!negatives.empty()) {
		radix_sort_positives_seq(negatives);
		std::reverse(negatives.begin(), negatives.end());
		for (int& num : negatives) {
			num = -num;
		}
	}

	if (!positives.empty()) {
		radix_sort_positives_seq(positives);
	}

	std::copy(negatives.begin(), negatives.end(), output);
	std::copy(positives.begin(), positives.end(), output + negatives.size());
}

void savchenko_m_radix_sort_seq::Sorter::counting_sort_seq(std::vector<int>& arr, int exp) {
	std::vector<int> output(arr.size());
	std::vector<int> count(10, 0);

	for (int num : arr) {
		int digit = (num / exp) % 10;
		count[digit]++;
	}

	std::partial_sum(count.begin(), count.end(), count.begin());

	for (size_t i = arr.size(); i > 0; i--) {
		int digit = (arr[i - 1] / exp) % 10;
		output[count[digit] - 1] = arr[i - 1];
		count[digit]--;
	}

	arr = output;
}

void savchenko_m_radix_sort_seq::Sorter::radix_sort_positives_seq(std::vector<int>& arr) {
	if (arr.empty()) {
		return;
	}

	int max = *std::max_element(arr.begin(), arr.end());
	for (int exp = 1; max / exp > 0; exp *= 10) {
		counting_sort_seq(arr, exp);
	}
}

// OMP

void savchenko_m_radix_sort_seq::Sorter::radix_sort_omp(int* input, int* output, size_t n) {

	throw "NOT IMPLEMENTED";
}

void savchenko_m_radix_sort_seq::Sorter::counting_sort_omp(std::vector<int>& arr, int exp) {

	throw "NOT IMPLEMENTED";
}

void savchenko_m_radix_sort_seq::Sorter::radix_sort_positives_omp(std::vector<int>& arr) {

	throw "NOT IMPLEMENTED";
}

// TBB

void savchenko_m_radix_sort_seq::Sorter::radix_sort_tbb(int* input, int* output, size_t n) {

	throw "NOT IMPLEMENTED";
}

void savchenko_m_radix_sort_seq::Sorter::counting_sort_tbb(std::vector<int>& arr, int exp) {

	throw "NOT IMPLEMENTED";
}

void savchenko_m_radix_sort_seq::Sorter::radix_sort_positives_tbb(std::vector<int>& arr) {

	throw "NOT IMPLEMENTED";
}