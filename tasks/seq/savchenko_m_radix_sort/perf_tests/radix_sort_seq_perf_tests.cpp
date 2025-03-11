#include <gtest/gtest.h>

#include <chrono>

#include "seq/savchenko_m_radix_sort/include/sorter.hpp"
#include "seq/savchenko_m_radix_sort/include/util.hpp"

namespace savchenko_m_radix_sort_seq {
	bool create_and_sort(size_t n, int min, int max){
		savchenko_m_radix_sort_seq::Sorter sorter;
		savchenko_m_radix_sort_seq::Util util;
		
		std::vector<int> input = util.random_vector_int(n, min, max);
		std::vector<int> output(n, 0);
		
		sorter.radix_sort_seq(input.data(), output.data(), n);
		
		return util.is_sorted(output.data(), n);
	}
}

TEST(savchenko_m_radix_sort_seq, perf_test) {
	const size_t n = 500000;
	const int min = 0;
	const int max = 500000;
	
	savchenko_m_radix_sort_seq::Sorter sorter;
	savchenko_m_radix_sort_seq::Util util;
		
	std::vector<int> input = util.random_vector_int(n, min, max);
	std::vector<int> output(n, 0);
	
	auto start = std::chrono::high_resolution_clock::now();
	
	auto end = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> duration = end - start;
	std::cout << "array size: " << n << endl;
	std::cout << "range: [" << min << ", " << max << "]" << endl;
	std::cout << "time: " << duration.count() << " s." << endl;
}