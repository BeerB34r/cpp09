#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <tuple>

class	RPN {
public:
	RPN() = delete;
	RPN(const RPN&) = delete;
	RPN& operator =(const RPN&) = delete;
	virtual ~RPN() = delete;
	// No internal state, no instantiation!!!!

	static std::tuple<bool,int>	calculate(const std::string);
private:
protected:
};

#endif // RPN_HPP
