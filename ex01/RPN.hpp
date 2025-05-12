#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <tuple>

class	RPN {
public:
	RPN();
	RPN(const RPN&);
	RPN& operator =(const RPN&);
	virtual ~RPN();

	static std::tuple<bool,int>	calculate(const std::string);
private:
protected:
};

#endif // RPN_HPP
