#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>

void	PmergeMe::sort(std::vector<int>& nums) {
	(void)nums;
}

static std::deque<int>	pairwiseSort(const std::deque<int> &other) {
	std::deque<int>	out = other;

	for (std::deque<int>::iterator it = out.begin() + 1; it != out.end() && it - 1 != out.end(); it += 2) {
		if (*it < *(it - 1)) std::swap(*it, *(it - 1));
	}

	return out;
}

static std::deque<int>	grab_a(const std::deque<int> &other) {
	std::deque<int>	out;

	for (std::deque<int>::const_iterator it = other.begin() + 1; it != other.end() && it - 1 != out.end(); it += 2) {
		out.push_back(*it);
	}

	return out;
}

static std::deque<int>	grab_b(const std::deque<int> &other) {
	std::deque<int>	out;

	for (std::deque<int>::const_iterator it = other.begin() + 1; it != other.end() && it - 1 != out.end(); it += 2) {
		out.push_back(*(it - 1));
	}
	if (other.size() % 2) out.push_back(other.back());
	return out;
}

static void	print_array(const std::deque<int>& nums, const std::string& name) {
	std::cout.width(10);
	std::cout << name + ":";
	std::cout.width();
	std::cout << "[";
	for (auto it = nums.begin(); it != nums.end(); it++) {
		std::cout.width(10);
		std::cout << *it;
		std::cout.width();
		std::cout << ", ";
	}
	std::cout << "]" << std::endl;
}
void	PmergeMe::sort(std::deque<int>& nums) {
	if (nums.size() < 2)
		return ;

	// the :sparkles: preamble :sparkles:
	const std::deque<int>					K	= nums; // original set of numbers K
	const std::deque<int>					K_p	= pairwiseSort(K); // pairwise sorted set of numbers K 
	std::deque<int>							A	= grab_a(K_p);
	const std::deque<int>					A_i	= A;
	std::deque<int>							B	= grab_b(K_p);
	const std::deque<int>					B_i	= B;

	print_array(K_p, "K_p");
	print_array(A, "A");
	print_array(B, "B");
	std::sort(A.begin(), A.end()); // TODO: NOT USE PLACEHOLDER
	print_array(A, "sorted A");
}
