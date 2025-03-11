#include "seq/savchenko_m_radix_sort/include/util.hpp"

#include <random>

int savchenko_m_radix_sort_seq::Util::random_int(const int min, const int max) const{
	if (min > max) {
		throw std::invalid_argument("ERROR: min should not be greater than max");
	}

	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_int_distribution<> dist(min, max);

	return dist(gen);
}

std::vector<int> savchenko_m_radix_sort_seq::Util::random_vector_int(const size_t n, const int min, const int max) const{
	if (n <= 0) {
		throw std::out_of_range("ERROR: n must be greater than 0");
	}
	if (min > max) {
		throw std::invalid_argument("ERROR: min should not be greater than max");
	}

	std::vector<int> vec(n, 0);
	for (size_t i = 0; i < n; i++) {
		vec[i] = random_int(min, max);
	}

	return vec;
}