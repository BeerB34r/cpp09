#ifndef BITCOINEXCHANGE_CPP
# define BITCOINEXCHANGE_CPP

#include <map>
#include <string>
#include <ctime>

class	BitcoinExchange	{
public:
	BitcoinExchange();
	BitcoinExchange(const std::string& databasePath);
	BitcoinExchange(const BitcoinExchange& other);
	virtual BitcoinExchange& operator =(const BitcoinExchange& other);
	~BitcoinExchange();

	float	getPrice(std::string timestring, float balance);
private:
	std::map<std::size_t,float>	openDatabase(std::string path);
	static const std::string	defaultDatabasePath;
	const std::string	databasePath = defaultDatabasePath;
	const std::map<std::size_t,float>	database = openDatabase(databasePath);
protected:
};

#endif // BITCOINEXCHANGE_CPP
