#include <gtest/gtest.h>

#include <chrono>

#include "seq/savchenko_m_radix_sort/include/sorter.hpp"
#include "seq/savchenko_m_radix_sort/include/util.hpp"

namespace savchenko_m_radix_sort_seq {
	bool create_and_sort(size_t n, int min, int max) {
		savchenko_m_radix_sort_seq::Sorter sorter;
		savchenko_m_radix_sort_seq::Util util;

		std::vector<int> input = util.random_vector_int(n, min, max);
		std::vector<int> output(n, 0);

		auto start = std::chrono::high_resolution_clock::now();
		sorter.radix_sort_seq(input.data(), output.data(), n);
		auto end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> duration = end - start;
		std::cout << "array size: " << n << std::endl;
		std::cout << "range: [" << min << ", " << max << "]" << std::endl;
		std::cout << "time: " << duration.count() << " s." << std::endl;

		return sorter.is_sorted(output.data(), n);
	}
}

TEST(savchenko_m_radix_sort_seq, perf_test1) {
	const size_t n = 50000000; // 50.000.000
	const int min = 0;
	const int max = 100000;
	
	ASSERT_TRUE(savchenko_m_radix_sort_seq::create_and_sort(n, min, max));
}

TEST(savchenko_m_radix_sort_seq, perf_test2) {
	const size_t n = 50000000; // 50.000.000
	const int min = -100000;
	const int max = 100000;

	ASSERT_TRUE(savchenko_m_radix_sort_seq::create_and_sort(n, min, max));
}

TEST(savchenko_m_radix_sort_seq, perf_test3) {
	const size_t n = 50000000; // 50.000.000
	const int min = 0;
	const int max = 100;

	ASSERT_TRUE(savchenko_m_radix_sort_seq::create_and_sort(n, min, max));
}

TEST(savchenko_m_radix_sort_seq, perf_test4) {
	const size_t n = 50000000; // 50.000.000
	const int min = -100;
	const int max = 100;

	ASSERT_TRUE(savchenko_m_radix_sort_seq::create_and_sort(n, min, max));
}

TEST(savchenko_m_radix_sort_seq, perf_test_MIN_MAX_INT) {
	const size_t n = 50000000; // 50.000.000
	const int min = INT_MIN;
	const int max = INT_MAX;

	ASSERT_TRUE(savchenko_m_radix_sort_seq::create_and_sort(n, min, max));
}