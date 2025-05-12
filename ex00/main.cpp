#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int ac, char **av) {
	try {
		BitcoinExchange	wallStreet;

		if (ac != 2) {
			std::cerr << "USAGE: " << av[0] << " {YYYY-MM-DD} " << std::endl;
			return 1;
		}
		try {
			std::cout << "price of 1 btc at " << av[1] << " = " << wallStreet.getPrice(av[1], 1) << std::endl;
		} catch (std::exception& err) {
			std::cerr << err.what() << std::endl;
		}
	} catch (std::exception& err) {
		std::cerr << err.what() << std::endl;
	}
}
