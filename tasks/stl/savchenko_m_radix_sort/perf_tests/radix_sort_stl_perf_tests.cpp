#include <gtest/gtest.h>

#include <climits>
#include <chrono>

#include "stl/savchenko_m_radix_sort/include/sorter.hpp"
#include "stl/savchenko_m_radix_sort/include/util.hpp"

namespace savchenko_m_radix_sort_stl {
	bool create_and_sort(size_t n, int min, int max) {
		savchenko_m_radix_sort::Sorter sorter;
		savchenko_m_radix_sort::Util util;

		std::vector<int> input = util.random_vector_int(n, min, max, 0); // seed = 0
		std::vector<int> output(n, 0);

		sorter.radix_sort_stl(input.data(), output.data(), n); // stl

		std::cout << "array size: " << n << std::endl;
		std::cout << "range: [" << min << ", " << max << "]" << std::endl;


		return sorter.is_sorted(output.data(), n);
	}
}

TEST(savchenko_m_radix_sort_stl, perf_test1) {
	const size_t n = 250000000; // 250.000.000
	const int min = 0;
	const int max = 100000;

	ASSERT_TRUE(savchenko_m_radix_sort_stl::create_and_sort(n, min, max));
}

TEST(savchenko_m_radix_sort_stl, perf_test2) {
	const size_t n = 250000000; // 250.000.000
	const int min = -100000;
	const int max = 100000;

	ASSERT_TRUE(savchenko_m_radix_sort_stl::create_and_sort(n, min, max));
}

TEST(savchenko_m_radix_sort_stl, perf_test3) {
	const size_t n = 250000000; // 250.000.000
	const int min = 0;
	const int max = 100;

	ASSERT_TRUE(savchenko_m_radix_sort_stl::create_and_sort(n, min, max));
}

TEST(savchenko_m_radix_sort_stl, perf_test4) {
	const size_t n = 250000000; // 250.000.000
	const int min = -100;
	const int max = 100;

	ASSERT_TRUE(savchenko_m_radix_sort_stl::create_and_sort(n, min, max));
}

TEST(savchenko_m_radix_sort_stl, perf_test_MIN_MAX_INT) {
	const size_t n = 250000000; // 250.000.000
	const int min = INT_MIN;
	const int max = INT_MAX;

	ASSERT_TRUE(savchenko_m_radix_sort_stl::create_and_sort(n, min, max));
}
