#include "PmergeMe.hpp"
#include <iostream>
#include <random>

#define ElementCount 11

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

int	main(int argc [[maybe_unused]], char **av [[maybe_unused]]) {
	std::random_device	device;
	std::mt19937		twister(device());
	std::uniform_int_distribution<std::mt19937::result_type>	rand(1, std::pow(10, 9));

	std::deque<int>	original;

	for (unsigned int i = 0; i < ElementCount; i++)
		original.push_back(rand(twister));

	std::deque<int>	copy = original;
	print_array(original, "original");
	PmergeMe::sort(copy);
}
