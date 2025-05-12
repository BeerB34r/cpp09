#include "BitcoinExchange.hpp"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

const std::string	BitcoinExchange::defaultDatabasePath = "./data.csv";

BitcoinExchange::BitcoinExchange() : databasePath(defaultDatabasePath), database(openDatabase(databasePath)) {
	std::clog << "default BitcoinExchange constructor called" << std::endl;
}
BitcoinExchange::BitcoinExchange(const std::string& databasePath) : databasePath(databasePath), database(openDatabase(databasePath)) {
	std::clog << "string BitcoinExchange constructor called" << std::endl;
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : databasePath(other.databasePath), database(other.database) {
	std::clog << "copy BitcoinExchange constructor called" << std::endl;
}

BitcoinExchange&	BitcoinExchange::operator =(const BitcoinExchange& other) {
	std::clog << "copy assignment BitcoinExchange operator called" << std::endl;
	std::cerr << "all members of BitcoinExchange are constant, do not use this operator if you expect something to happen" << std::endl;

	(void)other;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {
	std::clog << "default BitcoinExchange destructor called" << std::endl;
}

float	BitcoinExchange::getPrice(std::string timestring, float balance) {
	if (balance < 1)
		throw std::invalid_argument("balance must be positive, non-zero value");
	if (balance > 1000)
		throw std::invalid_argument("balance must be less than 1000");

	std::tm	timestamp;
	std::istringstream	iss(timestring);

	iss >> std::get_time(&timestamp, "%Y-%m-%d");
	if (iss.fail())
		throw std::invalid_argument("failed to parse \"" + timestring + "\"");

	std::size_t	key = timestamp.tm_year * 10000 + timestamp.tm_mon * 100 + timestamp.tm_mday;

	auto it = database.upper_bound(key);
	if (it == database.begin())
		throw std::out_of_range("provided timestamp is older than the oldest entry in database");
	it--;
	return it->second * balance;
}

std::map<std::size_t,float>	BitcoinExchange::openDatabase(std::string path) {
	std::ifstream	infile(path);
	std::map<std::size_t,float>	out;

	if (infile.fail())
		throw std::runtime_error("ifstream failed to open");
	std::string current;
	do {
		std::getline(infile, current);
		if (current.empty() || current == "date,exchange_rate") continue ;
		std::tm	timestamp;
		std::istringstream	iss(current);
		iss >> std::get_time(&timestamp, "%Y-%m-%d");
		if (iss.fail())
			throw std::runtime_error("formatting error in database: " + current);
		std::size_t	key = timestamp.tm_year * 10000 + timestamp.tm_mon * 100 + timestamp.tm_mday;
		float	value = std::stof(current.substr(current.find(',') + 1));
		bool	success;
		std::tie(std::ignore, success) = out.insert(std::pair<std::size_t, float>(key, value));
		if (!success)
			throw std::logic_error("database contains duplicate dates");
	}	while (!infile.eof());
	return out;
}
