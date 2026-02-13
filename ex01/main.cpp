#include "RPN.hpp"

#include <iostream>

int	main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Usage: " << av[0] << "\"<RPN string>\""  << std::endl;
		return 1;
	}
	bool	err;
	int		out;

	std::tie(err, out) = RPN::calculate(av[1]);
	if (err)
		return 1;
	std::cout << out << std::endl;
}
