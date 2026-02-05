#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int	main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "USAGE: " << av[0] << " {input.txt}" << std::endl;
		return 1;
	}
	try {
		BitcoinExchange	wallStreet;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}
	BitcoinExchange	wallStreet;
	std::ifstream	infile(av[1]);
	if (infile.fail()) {
		std::cerr << "Failed to open " << av[1] << std::endl;
		return 2;
	}
	std::string	current;
	do {
		std::getline(infile, current);
		if (current.empty() || current == "date | value") continue ;
		try {
			if (current.find('|') == std::string::npos) throw std::logic_error("malformed input => " + current);
			std::string	timestring = current.substr(0, current.find('|') - 1);
			std::string	balance = current.substr(current.find('|') + 1);
			float	price = wallStreet.getPrice(timestring, std::stof(balance));
			std::cout << timestring << "=>" << balance << " = " << price << std::endl;
		}	catch(std::exception& err) {
			std::cerr << "Error: " << err.what() << std::endl;
		}
	} while (!infile.eof());
}
