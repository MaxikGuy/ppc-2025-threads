#include "omp/savchenko_m_radix_sort/include/sorter.hpp"

#include <algorithm>
#include <climits>
#include <cstdint>
#include <stdexcept>
#include <omp.h>
#include <chrono>

#include <iostream>

bool savchenko_m_radix_sort::Sorter::is_sorted(int* arr, size_t n) const{
	if (n <= 0) {
		throw std::out_of_range("ERROR: n must be greater than 0");
	}
	if (arr == nullptr) {
		throw std::invalid_argument("ERROR: arr should not be NULL");
	}
	
	bool flag = true;
	#pragma omp parallel for shared(flag) schedule(static)
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			#pragma omp critical
			flag = false;
			break;
		}
	}

	return flag;
}

uint8_t  savchenko_m_radix_sort::Sorter::get_byte(int num, int byte_pos) const {
	uint32_t shifted = num - INT_MIN; // Convert `int` to `uint` so that negatives come before positives.
	uint8_t byte = (shifted >> (byte_pos * 8)) & 0xFF;
	return byte;
}

// SEQ

void savchenko_m_radix_sort::Sorter::radix_sort_seq(int* input, int* output, size_t n) {
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
	std::vector<int> arr(n);
	std::copy(input, input + n, arr.data());

	// radix sort
	auto start = std::chrono::high_resolution_clock::now();
	const int byte_count = sizeof(int); // 4 bytes
	for (int byte_pos = 0; byte_pos < byte_count; byte_pos++) {
		counting_sort_seq(arr, byte_pos);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "seq_time: " << duration.count() << " s." << std::endl;

	// post processing
	std::copy(arr.begin(), arr.end(), output);
}

void savchenko_m_radix_sort::Sorter::counting_sort_seq(std::vector<int>& arr, int byte_pos) {
	size_t n = arr.size();
	const int range = 256;
	std::vector<int> output(n);
	std::vector<int> count(range, 0);

	for (int i = 0; i < n; i++) {
		uint8_t byte = get_byte(arr[i], byte_pos);
		count[byte]++;
	}
	
	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--) {
		uint8_t byte = get_byte(arr[i], byte_pos);
		count[byte]--;
		output[count[byte]] = arr[i];
	}

	arr = std::move(output);
}

// OMP

void savchenko_m_radix_sort::Sorter::radix_sort_omp(int* input, int* output, size_t n) {
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
	std::vector<int> arr(n);
	std::copy(input, input + n, arr.data());

	// radix sort
	auto start = std::chrono::high_resolution_clock::now();
	const int byte_count = sizeof(int); // 4 bytes
	for (int byte_pos = 0; byte_pos < byte_count; byte_pos++) {
		counting_sort_omp(arr, byte_pos);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "omp_time: " << duration.count() << " s." << std::endl;

	// post processing
	std::copy(arr.begin(), arr.end(), output);
}

void savchenko_m_radix_sort::Sorter::counting_sort_omp(std::vector<int>& arr, int byte_pos) {
	size_t n = arr.size();
	const int range = 256;
	std::vector<int> output(n);
	
	int thread_count = omp_get_max_threads();
	std::vector<std::vector<int>> local_counts(thread_count, std::vector<int>(range, 0));

	#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		size_t chunk_size = (n + thread_count - 1) / thread_count;
		size_t start = tid * chunk_size;
		size_t end = std::min(start + chunk_size, n);

		for (size_t i = start; i < end; i++) {
			uint8_t byte = get_byte(arr[i], byte_pos);
			local_counts[tid][byte]++;
		}
	}

	std::vector<int> count(range, 0);
	for (int t = 0; t < thread_count; t++) {
		for (int i = 0; i < range; i++) {
			count[i] += local_counts[t][i];
		}
	}

	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	for (size_t i = n; i > 0; i--) {
		uint8_t byte = get_byte(arr[i - 1], byte_pos);
		count[byte]--;
		output[count[byte]] = arr[i - 1];
	}

	arr = std::move(output);
}

// TBB

void savchenko_m_radix_sort::Sorter::radix_sort_tbb(int* input, int* output, size_t n) {

	throw "NOT IMPLEMENTED";
}

void savchenko_m_radix_sort::Sorter::counting_sort_tbb(std::vector<int>& arr, int byte_pos) {

	throw "NOT IMPLEMENTED";
}
