#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>

template <typename T>
[[maybe_unused]] static void	_print_array(const T& nums, const std::string& name) {
	std::cout.width(10);
	std::cout << name + ":";
	std::cout.width();
	std::cout << "[";
	for (auto it = nums.begin(); it != nums.end() - 1; it++) {
		std::cout.width(2);
		std::cout << *it;
		std::cout.width();
		std::cout << ", ";
	}
	std::cout.width(2);
	std::cout << *(nums.end() - 1);
	std::cout.width();
	std::cout << "]" << std::endl;
}
#define print_array(x) (_print_array(x, #x))

// dynamic programming got me like
size_t PmergeMe::jacobsthalSequence(size_t n) {
	static std::vector<size_t>	memo({0, 1}); // arbitrary, used for memoization

	if (memo.size() > n)
		return memo[n];
	for (size_t i = memo.size() - 1; i < n; i++) {
		memo.push_back((1 << (i)) - memo[i]);
	}
	return memo[n];
}

void	PmergeMe::sort(std::vector<int>& X) {
	using container = std::vector<int>;
	using iterType = container::iterator;

	if (X.size() < 2)
		return ;
	container	larger(X.begin(), X.begin() + (X.size() / 2));
	container	smaller(X.begin() + (X.size() / 2), X.end());
	for (iterType big = larger.begin(), small = smaller.begin();
		big != larger.end();
		big++, small++) {
		if (*big < *small) std::swap(*big, *small);
	}
	container	S(larger);
	container	s;
	sort(S);
	for (size_t i = 0; i < S.size(); i++) {
		for (size_t j = 0; j < larger.size(); j++) {
			if (S[i] == larger[j]) {
				larger[j] = -1;
				s.insert(s.end(), smaller[j]);
			}
		}
	}
	if (!(s.size() % 2))
		s.insert(s.end(), *(smaller.end() - 1));
	S.insert(S.begin(), s[0]);
	std::size_t	upper_bound = s.size();
	std::size_t	lower_bound = 0;
	std::size_t	jacobsthal = 3;
	do {
		for (size_t i = std::min(jacobsthalSequence(jacobsthal), upper_bound) - 1; i > lower_bound; i--) {
			S.insert(std::upper_bound(S.begin(), S.end(), s[i]), s[i]);
		}
		lower_bound = jacobsthalSequence(jacobsthal++) - 1;
	}	while (jacobsthalSequence(jacobsthal) <= upper_bound);
	X = S;
}

void	PmergeMe::sort(std::deque<int>& X) {
	using container = std::deque<int>;
	using iterType = container::iterator;
	// Base case
	if (X.size() < 2)
		return ;
	// step 1, arbitrary pairs, leaving one element unpaired if isEven(X.size())
	container	larger(X.begin(), X.begin() + (X.size() / 2));
	container	smaller(X.begin() + (X.size() / 2), X.end());
	// step 2, pairwise comparisons
	for (iterType big = larger.begin(), small = smaller.begin();
		big != larger.end();
		big++, small++) {
		if (*big < *small) std::swap(*big, *small);
	}

	// step 3, recurse
	container		S(larger);
	container		s;
	sort(S);
	// step 3.5, associate the sorted (larger) elements with their pairs
	for (size_t i = 0; i < S.size(); i++) {
		for (size_t j = 0; j < larger.size(); j++) {
			if (S[i] == larger[j]) {
				larger[j] = -1;
				s.insert(s.end(), smaller[j]);
			}
		}
	}
	if (!(s.size() % 2))
		s.insert(s.end(), *(smaller.end() - 1));
	// step 4, insert pair of smallest elem onto start of S
	S.insert(S.begin(), s[0]);
	
	// step 5, binary insertion based on jacobsthal numbers
	std::size_t	upper_bound = s.size();
	std::size_t	lower_bound = 0; // rightmost element of s that has been inserted onto the main chain
	std::size_t	jacobsthal = 3; // lowest relevant N
	do {
		for (size_t i = std::min(jacobsthalSequence(jacobsthal), upper_bound) - 1; i > lower_bound; i--) {
			S.insert(std::upper_bound(
						S.begin(),
						S.end(),
						s[i]),
					s[i]);
		}
		lower_bound = jacobsthalSequence(jacobsthal++) - 1;
	} while (jacobsthalSequence(jacobsthal) <= upper_bound);
	X = S;
}
