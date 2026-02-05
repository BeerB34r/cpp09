#include "PmergeMe.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <chrono>

#define elementCount 30
#define maxNumWidth 2

[[maybe_unused]] static void	_print_array(const std::deque<int>& nums, const std::string& name) {
	std::cout.width(10);
	std::cout << name + ":";
	std::cout.width();
	std::cout << "[";
	for (auto it = nums.begin(); it != nums.end() - 1; it++) {
		std::cout.width(maxNumWidth);
		std::cout << *it;
		std::cout.width();
		std::cout << ", ";
	}
	std::cout.width(maxNumWidth);
	std::cout << *(nums.end() - 1);
	std::cout.width();
	std::cout << "]" << std::endl;
}
#define print_array(x) (_print_array(x, #x))

int	random_seq(void) {
	std::random_device	device; std::mt19937		twister(device()); std::uniform_int_distribution<std::mt19937::result_type>	rand(1, std::pow(10, maxNumWidth));

	std::deque<int>	original;

	for (unsigned int i = 0; i < elementCount; i++)
		original.push_back(rand(twister));
	std::deque<int>	pmerge = original;
	PmergeMe::sort(pmerge);
	std::cout << "pmerge is " << (std::is_sorted(pmerge.begin(), pmerge.end()) ? "" : "not ") << "sorted" << std::endl;
	std::deque<int>	sorted = original;
	std::sort(sorted.begin(), sorted.end());
	bool	equal = true;
	for (size_t i = 0; equal && i < sorted.size(); i++) {
		equal = pmerge[i] == sorted[i];
	}
	if (!equal) {
		std::cout << "some elements have been overridden" << std::endl;
		print_array(sorted);
		print_array(pmerge);
		return (1);
	}
	else std::cout << "Everything seems alright!" << std::endl;
	return (!std::is_sorted(pmerge.begin(), pmerge.end()));
}

std::chrono::duration<double,std::micro>	stopwatch(std::function<void()> fn) {
	std::chrono::time_point start = std::chrono::high_resolution_clock::now();
	fn();
	std::chrono::time_point end = std::chrono::high_resolution_clock::now();
	return (end - start);
}

int	test(std::deque<int> dq, std::vector<int> vec) {
	std::vector<int>	reference(vec);
	std::sort(reference.begin(), reference.end());
	std::cout << "Unsorted positive integer sequence:";
	for (int i : vec) std::cout << " " << i;
	std::cout << std::endl;
	std::cout << "Sorted positive integer sequence";
	for (int i : reference) std::cout << " " << i;
	std::cout << std::endl;
	std::cout << "Time to process range of ";
	std::cout.width(10);
	std::cout << vec.size();
	std::cout.width();
	std::cout << " elements using std::vector<int> : ";
	std::cout.precision(9);
	std::cout << stopwatch([&vec](){ PmergeMe::sort(vec); });
	std::cout.precision();
	std::cout << " μs" << std::endl;
	std::cout << "Time to process range of ";
	std::cout.width(10);
	std::cout << dq.size();
	std::cout.width();
	std::cout << " elements using std::deque<int> : ";
	std::cout.precision(9);
	std::cout << stopwatch([&dq](){ PmergeMe::sort(dq); });
	std::cout.precision();
	std::cout << " μs" << std::endl;
	PmergeMe::sort(dq);
	PmergeMe::sort(vec);
	for (size_t i = 0; i < reference.size(); i++) {
		if (reference[i] != vec[i] || reference[i] != dq[i]) {
			std::cerr << "pos[" << i << "]r[" << reference[i] << "]v[" << vec[i] << "]d[" << dq[i] << "]" << std::endl;
			std::cerr << "ref.size(): " << reference.size() << std::endl;
			std::cerr << "vec.size(): " << vec.size() << std::endl;
			std::cerr << "dq.size(): " << dq.size() << std::endl;
			return 1;
		}
	}
	return 0;
}

int	main(int ac, char **av) {
	if (ac == 1)
		return (random_seq());

	std::vector<std::string>	arg(av + 1, av + ac);
	std::vector<int>	vec;
	std::deque<int>		dq;
	for (std::string& s : arg) {
		int i;
		try {
			i = std::stoi(s);
			if (i < 0) {
				std::cerr << "PMergeMe requires a positive integer sequence only." << std::endl;
				return (1);
			}
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			return (1);
		}
		vec.insert(vec.end(), i);
		dq.insert(dq.end(), i);
	}
	return (test(dq, vec));
}
